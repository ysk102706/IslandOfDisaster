// Fill out your copyright notice in the Description page of Project Settings.


#include "IngredientItemListUI.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../Manager/Managers.h"
#include "../Actor/Player/CPP_Player.h"
#include "../Actor/Item/Inventory.h"

void UIngredientItemListUI::Init(UTexture2D* Texture, FString Name, FString Description, int Count)
{
	IMG_Item->SetBrushFromTexture(Texture);
	TItemName->SetText(FText::FromString(Name));
	TItemDescription->SetText(FText::FromString(Description)); 
	TItemCount->SetText(FText::FromString(FString::Printf(TEXT("<%d/%d>"), UManagers::Get(GetWorld())->Player()->Inventory->GetItemCount(Name), Count)));
}
