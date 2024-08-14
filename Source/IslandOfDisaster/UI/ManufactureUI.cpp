// Fill out your copyright notice in the Description page of Project Settings.


#include "ManufactureUI.h" 
#include "ManufacturedItemListUI.h"
#include "IngredientItemListUI.h"
#include "Components/ScrollBox.h" 
#include "Components/SizeBox.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../Manager/Managers.h"
#include "../Actor/Player/CPP_Player.h"
#include "../Actor/Item/Inventory.h"
#include "../Manager/DataLoadManager.h"

void UManufactureUI::NativeConstruct()
{
	Super::NativeConstruct();

	BManufacture->OnClicked.AddDynamic(this, &UManufactureUI::Manufacture);
}

void UManufactureUI::AddManufacturedItem(UTexture2D* Texture, int Id, FString Name)
{
	if (auto Item = CreateWidget<UManufacturedItemListUI>(this, ManufacturedItemListWidget)) {
		Item->Init(Texture, Id, Name);
		
		if (!ManufacturedItemHorizontalBoxs.Num() || ManufacturedItemHorizontalBoxs.Top()->GetChildrenCount() == 2) {
			ManufacturedItemHorizontalBoxs.Add(NewObject<UHorizontalBox>(this));
			SB_ManufacturedItemList->AddChild(ManufacturedItemHorizontalBoxs.Top());
		}

		if (auto SizeBox = NewObject<USizeBox>(this)) {
			SizeBox->SetWidthOverride(SB_ManufacturedItemListSize);
			SizeBox->SetHeightOverride(SB_ManufacturedItemListSize);

			SizeBox->AddChild(Item);

			if (auto HB_Slot = Cast<UHorizontalBoxSlot>(ManufacturedItemHorizontalBoxs.Top()->AddChild(SizeBox))) {
				HB_Slot->SetPadding(FMargin(0, ManufacturedItemListLineSpace, ManufacturedItemListLineSpace, 0));
			}
		}
	}
}

void UManufactureUI::SelectManufacturedItem(UTexture2D* Texture, int Id, FString Name, FString Description)
{
	IMG_Item->SetBrushFromTexture(Texture);
	TItemName->SetText(FText::FromString(Name));
	TItemDescription->SetText(FText::FromString(Description));
	SelectedItemId = Id;
}

void UManufactureUI::ResetIngredientItemList()
{
	while(SB_IngredientItemList->GetChildrenCount()) SB_IngredientItemList->RemoveChildAt(0);
	IngredientItemHorizontalBoxs.Reset();
	Ingredients.Reset();
}

void UManufactureUI::AddIngredientItem(UTexture2D* Texture, FString Name, FString Description, int Count)
{
	if (auto Item = CreateWidget<UIngredientItemListUI>(this, IngredientItemListWidget)) {
		Item->Init(Texture, Name, Description, Count);
		Ingredients.Add({ Name, Count });

		if (!IngredientItemHorizontalBoxs.Num() || IngredientItemHorizontalBoxs.Top()->GetChildrenCount() == 2) {
			IngredientItemHorizontalBoxs.Add(NewObject<UHorizontalBox>(this));
			SB_IngredientItemList->AddChild(IngredientItemHorizontalBoxs.Top());
		}

		if (auto SizeBox = NewObject<USizeBox>(this)) {
			SizeBox->SetWidthOverride(SB_IngredientItemListWidth);
			SizeBox->SetHeightOverride(SB_IngredientItemListHeight);

			SizeBox->AddChild(Item);

			if (auto HB_Slot = Cast<UHorizontalBoxSlot>(IngredientItemHorizontalBoxs.Top()->AddChild(SizeBox))) {
				HB_Slot->SetPadding(FMargin(0, IngredientItemListLineSpace, IngredientItemListLineSpace, 0));
			}
		}
	}
}

void UManufactureUI::Manufacture()
{
	if (isManufacture) {
		int Count = 0;
		auto Player = UManagers::Get(GetWorld())->Player();
		for (auto Data : Ingredients) Player->Inventory->Consume(Data.Name, Data.Count);
		UManagers::Get(GetWorld())->DataLoad()->LoadIngredientItems(GetWorld(), SelectedItemId);
		
		if (auto Item = UManagers::Get(GetWorld())->DataLoad()->SpawnItemActor(GetWorld(), SelectedItemId)) {
			Count = Item->ManufacturedItemCount - 1;
			if (!Item->Picked()) Item->Droped();
		}
		
		while (Count--){
			if (auto Item = UManagers::Get(GetWorld())->DataLoad()->SpawnItemActor(GetWorld(), SelectedItemId)) {
				if (!Item->Picked()) Item->Droped();
			}
		}
	}
}

void UManufactureUI::SetIsManufacture(bool Value)
{
	isManufacture = Value;
}
