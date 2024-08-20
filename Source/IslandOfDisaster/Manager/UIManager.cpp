// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "../UI/PlayerInfoUI.h"
#include "../UI/ManufactureUI.h"
#include "../UI/TitleUI.h"

#define CreateOrSetWidget(Object, Type) \
	if (!Type##Object) Type##Object = CreateWidget<U##Type##UI>(GetWorld(), Type##Widget); \
	Object = Type##Object; \

UUserWidget* UUIManager::GetWidget(EWidgetType Type) {
	UUserWidget* Object = nullptr;

	switch (Type) {
	case EWidgetType::PlayerInfo:
		CreateOrSetWidget(Object, PlayerInfo);
		break;
	case EWidgetType::Manufacture:
		CreateOrSetWidget(Object, Manufacture);
		break;
	case EWidgetType::Title:
		CreateOrSetWidget(Object, Title);
		break;
	}

	return Object;
}

void UUIManager::ShowWidget(EWidgetType Type)
{
	UUserWidget* Object = GetWidget(Type);
	if (Object) Object->AddToViewport();
}

void UUIManager::HideWidget(EWidgetType Type)
{
	UUserWidget* Object = GetWidget(Type);
	if (Object) Object->RemoveFromViewport();
}
