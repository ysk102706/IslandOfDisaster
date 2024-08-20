// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIManager.generated.h"

UENUM(BlueprintType)
enum class EWidgetType : uint8 {
	PlayerInfo		UMETA(DisplayName="PlayerInfo"),
	Manufacture		UMETA(DisplayName="Manufacture"),
	Title			UMETA(DisplayName="Title")
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ISLANDOFDISASTER_API UUIManager : public UObject
{
	GENERATED_BODY()
	
public:
	UUserWidget* GetWidget(EWidgetType Type);
	void ShowWidget(EWidgetType Type);
	void HideWidget(EWidgetType Type);

	UPROPERTY(EditAnywhere, Category=Widget)
	TSubclassOf<class UPlayerInfoUI> PlayerInfoWidget;
	UPROPERTY(EditAnywhere, Category = Widget)
	TSubclassOf<class UManufactureUI> ManufactureWidget;
	UPROPERTY(EditAnywhere, Category = Widget)
	TSubclassOf<class UTitleUI> TitleWidget;

	TObjectPtr<UUserWidget> PlayerInfoObject;
	TObjectPtr<UUserWidget> ManufactureObject;
	TObjectPtr<UUserWidget> TitleObject;

};
