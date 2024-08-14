// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IngredientItemListUI.generated.h"

/**
 * 
 */
UCLASS()
class ISLANDOFDISASTER_API UIngredientItemListUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init(UTexture2D* Texture, FString Name, FString Description, int Count);

private:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TItemName;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TItemDescription;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TItemCount;
	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Item;

};
