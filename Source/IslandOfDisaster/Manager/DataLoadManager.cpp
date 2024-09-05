// Fill out your copyright notice in the Description page of Project Settings.


#include "DataLoadManager.h"
#include "Managers.h"
#include "UIManager.h"
#include "../UI/ManufactureUI.h"
#include "../Actor/Player/CPP_Player.h"
#include "../Actor/Item/Inventory.h"
#include "../Actor/Item/Item.h"

#define Path FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir()) + "Database/ItemData.db"

void UDataLoadManager::LoadManufacturedItemList(const UWorld* World)
{
	Database = new FSQLiteDatabase();
	if (Database->Open(*(Path), ESQLiteDatabaseOpenMode::ReadWrite)) {
		int id = 0;
		FString Name = "";
		if (auto ManufactureWidget = Cast<UManufactureUI>(UManagers::Get(World)->UI()->GetWidget(EWidgetType::Manufacture))) {
			PStmt = new FSQLitePreparedStatement();
			const FString Query = "select id, name from item where isManufactured = 1";
			if (PStmt->Create(*Database, *Query, ESQLitePreparedStatementFlags::Persistent)) {
				while (PStmt->Step() == ESQLitePreparedStatementStepResult::Row) {
					PStmt->GetColumnValueByIndex(0, id);
					PStmt->GetColumnValueByIndex(1, Name);
					ManufactureWidget->AddManufacturedItem(Textures[id], id, Name);
				}
			}
			PStmt->Destroy();
			delete PStmt;
		}
	}
	Database->Close();
	delete Database;
}

void UDataLoadManager::LoadSelectedManufacturedItem(const UWorld* World, int Id)
{
	Database = new FSQLiteDatabase();
	if (Database->Open(*(Path), ESQLiteDatabaseOpenMode::ReadWrite)) {
		if (auto ManufactureWidget = Cast<UManufactureUI>(UManagers::Get(World)->UI()->GetWidget(EWidgetType::Manufacture))) {
			FString Name = "";
			FString Description = "";

			PStmt = new FSQLitePreparedStatement();
			const FString Query = "select name, description from item where id = $Id";
			if (PStmt->Create(*Database, *Query, ESQLitePreparedStatementFlags::Persistent)) {
				PStmt->SetBindingValueByName(TEXT("$Id"), Id);
				if  (PStmt->Step() == ESQLitePreparedStatementStepResult::Row) {
					PStmt->GetColumnValueByIndex(0, Name);
					PStmt->GetColumnValueByIndex(1, Description);
					ManufactureWidget->SelectManufacturedItem(Textures[Id], Id, Name, Description);
				}
			}
			PStmt->Destroy();
			delete PStmt;
		}
	}
	Database->Close();
	delete Database;
}

void UDataLoadManager::LoadIngredientItems(const UWorld* World, int Id)
{
	Database = new FSQLiteDatabase();
	if (Database->Open(*(Path), ESQLiteDatabaseOpenMode::ReadWrite)) {
		int IngredientId = 0;
		FString Name = "";
		FString Description = "";
		int Count = 0;

		bool isManufacture = true;

		if (auto ManufactureWidget = Cast<UManufactureUI>(UManagers::Get(World)->UI()->GetWidget(EWidgetType::Manufacture))) {
			ManufactureWidget->ResetIngredientItemList();

			PStmt = new FSQLitePreparedStatement();
			const FString Query = "select i.id, name, description, ingredientCount from manufacture, item i where manufacturedItemId = $Id and i.id = ingredientItemId";
			if (PStmt->Create(*Database, *Query, ESQLitePreparedStatementFlags::Persistent)) {
				PStmt->SetBindingValueByName(TEXT("$Id"), Id);
				while (PStmt->Step() == ESQLitePreparedStatementStepResult::Row) {
					PStmt->GetColumnValueByIndex(0, IngredientId);
					PStmt->GetColumnValueByIndex(1, Name);
					PStmt->GetColumnValueByIndex(2, Description);
					PStmt->GetColumnValueByIndex(3, Count);
					ManufactureWidget->AddIngredientItem(Textures[IngredientId], Name, Description, Count);
					if (isManufacture) isManufacture = UManagers::Get(World)->Player()->Inventory->GetItemCount(Name) >= Count;
				}
			}
			ManufactureWidget->SetIsManufacture(isManufacture);

			PStmt->Destroy();
			delete PStmt;
		}
	}
	Database->Close();
	delete Database;
}

TObjectPtr<AItem> UDataLoadManager::SpawnItemActor(UWorld* World, int Id)
{
	auto Player = UManagers::Get(World)->Player();
	FVector Position = FVector(0, 0, 0);
	FRotator Rotation = FRotator(0, 0, 0);
	
	auto Actor = World->SpawnActor(Items[Id], &Position, &Rotation);
	UManagers::Get(GetWorld())->SpawnedItems.Add(Actor);

	auto Item = Cast<AItem>(Actor);
	LoadItems(Id, Item);

	return Item;
}

void UDataLoadManager::LoadItems(int Id, AItem* Item)
{
	Database = new FSQLiteDatabase();
	if (Database->Open(*(Path), ESQLiteDatabaseOpenMode::ReadWrite)) {
		FString Name = "";
		FString Description = "";
		int ManufacturedItemCount = 0;
		int IsConstruct = false;
		int IsUsable = false;
		int Durability = 0;
		int IsExit = false;

		PStmt = new FSQLitePreparedStatement();
		const FString Query = "select name, description, manufacturedItemCount, isConstruct, isUsable, durability, isExit from item where id = $Id";
		if (PStmt->Create(*Database, *Query, ESQLitePreparedStatementFlags::Persistent)) {
			PStmt->SetBindingValueByName(TEXT("$Id"), Id);
			if (PStmt->Step() == ESQLitePreparedStatementStepResult::Row) {
				PStmt->GetColumnValueByIndex(0, Name);
				PStmt->GetColumnValueByIndex(1, Description);
				PStmt->GetColumnValueByIndex(2, ManufacturedItemCount);
				PStmt->GetColumnValueByIndex(3, IsConstruct);
				PStmt->GetColumnValueByIndex(4, IsUsable);
				PStmt->GetColumnValueByIndex(5, Durability);
				PStmt->GetColumnValueByIndex(6, IsExit);
				Item->Init(Textures[Id], Name, Description, ManufacturedItemCount, bool(IsConstruct), bool(IsUsable), Durability, bool(IsExit));
			}
		}
		PStmt->Destroy();
		delete PStmt;
	}
	Database->Close();
	delete Database;
}