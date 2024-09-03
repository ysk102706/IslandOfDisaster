// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Item.h"
#include "../../Manager/Managers.h"
#include "../../Manager/UIManager.h"
#include "../Player/CPP_Player.h"
#include "../../UI/PlayerInfoUI.h"
#include "../../Manager/DataLoadManager.h"

AInventory::AInventory()
{
	PrimaryActorTick.bCanEverTick = true;

	for (int i = 0; i < 7; i++) Contents[i].Add(nullptr);
	ContentMap = new TMap<FString, int>();
}

void AInventory::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInventory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TObjectPtr<AItem> AInventory::GetItem(int Idx)
{
	return Contents[Idx][0];
}

bool AInventory::AddItem(TObjectPtr<AItem> Item)
{
	for (int i = 0; i < 7; i++) {
		if (Contents[i][0]) {
			if (Contents[i][0]->Name == Item->Name) {
				Contents[i].Add(Item);
				if (auto Widget = Cast<UPlayerInfoUI>(UManagers::Get(World)->UI()->GetWidget(EWidgetType::PlayerInfo))) {
					Widget->ChangeInventoryItemCnt(i, FString::Printf(TEXT("%d"), Contents[i].Num()));
					(*ContentMap->Find(Item->Name))++;
				}
				return true;
			}
		}
	}

	for (int i = 0; i < 7; i++) {
		if (!Contents[i][0]) {
			Contents[i][0] = Item;
			if (auto Widget = Cast<UPlayerInfoUI>(UManagers::Get(World)->UI()->GetWidget(EWidgetType::PlayerInfo))) {
				Widget->ChangeInventoryItemTexture(i, Item->Texture);
				Widget->ChangeInventoryItemCnt(i, "1");
				ContentMap->Add(Item->Name, 1);
			}
			if (i == SelectedItemIdx) {
				if (Contents[i][0] && Contents[i][0]->IsConstruct) {
					IsConstruct = true;
					ConstructPointObject = UManagers::Get(World)->DataLoad()->SpawnItemActor(World, Contents[i][0]->Id);
					ConstructPointObject->IsConstructPoint = true;
				}
			}
			return true;
		}
	}
	return false;
}

void AInventory::DropItem()
{
	auto& item = Contents[SelectedItemIdx];
	if (item[0]) {
		(*ContentMap->Find(item[0]->Name))--;
		
		if (item.Num() == 1 && item[0]->IsConstruct) {
			ConstructPointObject->DestroyActor();
			ConstructPointObject = nullptr;
		}

		if (!*ContentMap->Find(item[0]->Name)) ContentMap->Remove(item[0]->Name);

		item[0]->Droped();
		item.RemoveAt(0);

		SetInventoryUI(SelectedItemIdx, item);
	}
}

void AInventory::SelectItem(int Idx)
{
	if (auto Widget = Cast<UPlayerInfoUI>(UManagers::Get(World)->UI()->GetWidget(EWidgetType::PlayerInfo))) {
		Widget->ChangeInventorySelectItem(SelectedItemIdx, Idx);
	}
	
	SelectedItemIdx = Idx;
	
	if (Contents[Idx][0] && Contents[Idx][0]->IsConstruct && !ConstructPointObject) {
		IsConstruct = true;

		ConstructPointObject = UManagers::Get(World)->DataLoad()->SpawnItemActor(World, Contents[Idx][0]->Id);
		ConstructPointObject->IsConstructPoint = true;
	}
	else if (ConstructPointObject) {
		ConstructPointObject->DestroyActor();
		ConstructPointObject = nullptr;
	}
}

void AInventory::ConstructItem()
{
	auto& Item = Contents[SelectedItemIdx];
	if (Item[0]->IsConstruct) {
		FVector Pos = ConstructPointObject->GetActorLocation();
		Item[0]->Construct(Pos);
		ConstructPointObject->DestroyActor();
		
		(*ContentMap->Find(Item[0]->Name))--;
		if (!(*ContentMap->Find(Item[0]->Name))) ContentMap->Remove(Item[0]->Name);

		Item.RemoveAt(0);
		SetInventoryUI(SelectedItemIdx, Item);

		SelectItem(SelectedItemIdx);
	}
}

void AInventory::SetWorld(UWorld* PlayerWorld)
{
	World = PlayerWorld;
}

void AInventory::SetNoneItemTexture(UTexture2D* Texture)
{
	NoneItemTexture = Texture;
}

void AInventory::SetInventoryUI(int Idx, TArray<TObjectPtr<AItem>>& Items)
{
	auto Widget = Cast<UPlayerInfoUI>(UManagers::Get(World)->UI()->GetWidget(EWidgetType::PlayerInfo));
	if (Widget) Widget->ChangeInventoryItemCnt(Idx, !Items.Num() ? "" : FString::Printf(TEXT("%d"), Items.Num()));
	if (!Items.Num()) {
		Items.Add(nullptr);
		if (Widget) Widget->ChangeInventoryItemTexture(Idx, NoneItemTexture);
	}
}

bool AInventory::ShowConstructPoint(FString HitObjectName, FVector HitPos)
{
	if (IsConstruct && ConstructPointObject) {
		ConstructPointObject->SetActorLocation(HitPos);
		ConstructPointObject->SetWorldLocation(HitPos);
		ConstructPointObject->ConstructPoint(HitObjectName == ConstructPointObject->ConstructAvailablePlaceName);
		return HitObjectName == ConstructPointObject->ConstructAvailablePlaceName;
	}
	return false;
}

int32 AInventory::GetItemCount(FString Name)
{
	if (ContentMap->Contains(Name)) return *ContentMap->Find(Name);
	return 0;
}

void AInventory::Consume(FString Name, int Count)
{
	int ItemIdx = 0;

	for (int i = 0; i < 7; i++) {
		if (Contents[i][0] && Contents[i][0]->Name == Name) {
			ItemIdx = i;
			break;
		}
	}

	if (Name == TEXT("도끼") || Name == TEXT("망치") || Name == TEXT("바늘")) {
		Contents[ItemIdx][0]->Durability--;
		if (!Contents[ItemIdx][0]->Durability) {
			Contents[ItemIdx][0]->DestroyActor();
			Contents[ItemIdx].RemoveAt(0);
		}
	}
	else while (Count--) {
		Contents[ItemIdx][0]->DestroyActor();
		Contents[ItemIdx].RemoveAt(0);
	}
	(*ContentMap->Find(Name)) = Contents[ItemIdx].Num();
	if (!(*ContentMap->Find(Name))) ContentMap->Remove(Name);

	SetInventoryUI(ItemIdx, Contents[ItemIdx]);
}

TObjectPtr<AItem> AInventory::GetSelectedItem()
{
	return Contents[SelectedItemIdx][0];
}
