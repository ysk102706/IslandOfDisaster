// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInfoUI.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../Manager/Managers.h"
#include "../Actor/Player/CPP_Player.h"

#define SetBGTexture(Idx, Texture) BG_Item##Idx->SetBrushFromTexture(Texture)
#define SetItemTexture(Idx, Texture) IMG_Item##Idx->SetBrushFromTexture(Texture)
#define SetCntText(Idx, Text) CNT_Item##Idx->SetText(FText::FromString(Text))

void UPlayerInfoUI::SetHP(float MaxHP, float CurHP) {
	HPBar->SetPercent(CurHP / MaxHP);
}

void UPlayerInfoUI::SetHunger(float MaxHunger, float CurHunger)
{
	HungerBar->SetPercent(CurHunger / MaxHunger);
}

void UPlayerInfoUI::SetThirsty(float MaxThirsty, float CurThirsty)
{
	ThirstyBar->SetPercent(CurThirsty / MaxThirsty);
}

void UPlayerInfoUI::SetTemperature(float MaxTemperature, float CurTemperature)
{
	TemperatureBar->SetPercent(CurTemperature / MaxTemperature);
}

void UPlayerInfoUI::SetHumidity(float MaxHumidity, float CurHumidity)
{
	HumidityBar->SetPercent(CurHumidity / MaxHumidity);
}

void UPlayerInfoUI::SetDays(int Days)
{
	FString Text = FString::Printf(TEXT("Day%d"), Days);
	TDays->SetText(FText::FromString(Text));
}

void UPlayerInfoUI::SetHours(int Hours, int Minutes)
{
	FString Text = FString::Printf(TEXT("%02d:%02d"), Hours, Minutes);
	THours->SetText(FText::FromString(Text));
}

void UPlayerInfoUI::ChangeInventorySelectItem(int LastIdx, int Idx)
{
	UTexture2D* NotSelectedBG = UManagers::Get(GetWorld())->Player()->GetNotSelectedItemBG();
	UTexture2D* SelectedBG = UManagers::Get(GetWorld())->Player()->GetSelectedItemBG();

	if (LastIdx == 0) SetBGTexture(1, NotSelectedBG);
	else if (LastIdx == 1) SetBGTexture(2, NotSelectedBG);
	else if (LastIdx == 2) SetBGTexture(3, NotSelectedBG);
	else if (LastIdx == 3) SetBGTexture(4, NotSelectedBG);
	else if (LastIdx == 4) SetBGTexture(5, NotSelectedBG);
	else if (LastIdx == 5) SetBGTexture(6, NotSelectedBG);
	else if (LastIdx == 6) SetBGTexture(7, NotSelectedBG);

	if (Idx == 0) SetBGTexture(1, SelectedBG);
	else if (Idx == 1) SetBGTexture(2, SelectedBG);
	else if (Idx == 2) SetBGTexture(3, SelectedBG);
	else if (Idx == 3) SetBGTexture(4, SelectedBG);
	else if (Idx == 4) SetBGTexture(5, SelectedBG);
	else if (Idx == 5) SetBGTexture(6, SelectedBG);
	else if (Idx == 6) SetBGTexture(7, SelectedBG);
}

void UPlayerInfoUI::ChangeInventoryItemTexture(int Idx, UTexture2D* Texture)
{
	if (Idx == 0) SetItemTexture(1, Texture);
	else if (Idx == 1) SetItemTexture(2, Texture);
	else if (Idx == 2) SetItemTexture(3, Texture);
	else if (Idx == 3) SetItemTexture(4, Texture);
	else if (Idx == 4) SetItemTexture(5, Texture);
	else if (Idx == 5) SetItemTexture(6, Texture);
	else if (Idx == 6) SetItemTexture(7, Texture);
}

void UPlayerInfoUI::ChangeInventoryItemCnt(int Idx, FString Text)
{
	if (Idx == 0) SetCntText(1, Text);
	else if (Idx == 1) SetCntText(2, Text);
	else if (Idx == 2) SetCntText(3, Text);
	else if (Idx == 3) SetCntText(4, Text);
	else if (Idx == 4) SetCntText(5, Text);
	else if (Idx == 5) SetCntText(6, Text);
	else if (Idx == 6) SetCntText(7, Text);
}
