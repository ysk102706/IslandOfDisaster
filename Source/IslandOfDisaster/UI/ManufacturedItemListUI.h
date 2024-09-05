// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManufacturedItemListUI.generated.h"

/**
 * 
 */
UCLASS()
class ISLANDOFDISASTER_API UManufacturedItemListUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void Init(UTexture2D* IMG, int Id, FString Name);

	UFUNCTION()
	void Select();

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Item;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TItemName;
	UPROPERTY(meta = (BindWidget))
	class UButton* BSelect;

	int ItemId;
	FString ItemName;

};
