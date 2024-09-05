// Fill out your copyright notice in the Description page of Project Settings.


#include "HelpUI.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "../Manager/Managers.h"
#include "../Manager/UIManager.h"
#include "../UI/TitleUI.h"
#include "Components/TextBlock.h"

void UHelpUI::NativeConstruct()
{
	Super::NativeConstruct();

	BPre->OnClicked.AddDynamic(this, &UHelpUI::PrePage);
	BNext->OnClicked.AddDynamic(this, &UHelpUI::NextPage);
	BClose->OnClicked.AddDynamic(this, &UHelpUI::Close);

	CurPage = 0;
	SetHelpImage();
	SetPage();
}

void UHelpUI::PrePage()
{
	if (CurPage > 0) {
		CurPage--;
		SetHelpImage();
		SetPage();
	}
}

void UHelpUI::NextPage()
{
	if (CurPage < HelpImages.Num() - 1) {
		CurPage++;
		SetHelpImage();
		SetPage();
	}
}

void UHelpUI::Close()
{
	Cast<UTitleUI>(UManagers::Get(GetWorld())->UI()->GetWidget(EWidgetType::Title))->IsHelpOpen = false;
	UManagers::Get(GetWorld())->UI()->HideWidget(EWidgetType::Help); 
}

void UHelpUI::SetPage()
{
	TPage->SetText(FText::FromString(FString::Printf(TEXT("%d/%d"), CurPage + 1, HelpImages.Num())));
}

void UHelpUI::SetHelpImage()
{
	IMG_Help->SetBrushFromTexture(HelpImages[CurPage]);
}
