// Fill out your copyright notice in the Description page of Project Settings.


#include "ManufacturedItemListUI.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../Manager/Managers.h"
#include "../Manager/DataLoadManager.h"

void UManufacturedItemListUI::NativeConstruct()
{
	Super::NativeConstruct();

	BSelect->OnClicked.Clear();
	BSelect->OnClicked.AddDynamic(this, &UManufacturedItemListUI::Select);
}

void UManufacturedItemListUI::Init(UTexture2D* IMG, int Id, FString Name)
{
	IMG_Item->SetBrushFromTexture(IMG);
	TItemName->SetText(FText::FromString(Name));

	ItemId = Id;
	ItemName = Name;
}

void UManufacturedItemListUI::Select()
{
	UManagers::Get(GetWorld())->DataLoad()->LoadSelectedManufacturedItem(GetWorld(), ItemId);
	UManagers::Get(GetWorld())->DataLoad()->LoadIngredientItems(GetWorld(), ItemId);
}
