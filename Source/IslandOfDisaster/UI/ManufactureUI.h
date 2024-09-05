// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ManufactureUI.generated.h"

struct IngredientItemData {
	FString Name;
	int Count;
};

/**
 * 
 */
UCLASS()
class ISLANDOFDISASTER_API UManufactureUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void AddManufacturedItem(UTexture2D* Texture, int Id, FString Name);
	UFUNCTION()
	void SelectManufacturedItem(UTexture2D* Texture, int Id, FString Name, FString Description);
	UFUNCTION()
	void ResetIngredientItemList();
	UFUNCTION()
	void AddIngredientItem(UTexture2D* Texture, FString Name, FString Description, int Count);

	UFUNCTION()
	void Manufacture();
	
	UFUNCTION()
	void SetIsManufacture(bool Value);

	UPROPERTY(EditAnywhere, Category=Widget)
	TSubclassOf<class UManufacturedItemListUI> ManufacturedItemListWidget;
	UPROPERTY(EditAnywhere, Category=Widget)
	float SB_ManufacturedItemListSize;
	UPROPERTY(EditAnywhere, Category = Widget)
	float ManufacturedItemListLineSpace;

	UPROPERTY(EditAnywhere, Category = Widget)
	TSubclassOf<class UIngredientItemListUI> IngredientItemListWidget;
	UPROPERTY(EditAnywhere, Category = Widget)
	float SB_IngredientItemListWidth;
	UPROPERTY(EditAnywhere, Category = Widget)
	float SB_IngredientItemListHeight;
	UPROPERTY(EditAnywhere, Category = Widget)
	float IngredientItemListLineSpace;

private:
	UPROPERTY(meta=(BindWidget))
	class UScrollBox* SB_ManufacturedItemList;
	UPROPERTY(meta = (BindWidget))
	class UScrollBox* SB_IngredientItemList;

	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Item;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TItemName;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TItemDescription;

	UPROPERTY(meta = (BindWidget))
	class UButton* BManufacture;

	UPROPERTY()
	TArray<class UHorizontalBox*> ManufacturedItemHorizontalBoxs;
	UPROPERTY()
	TArray<class UHorizontalBox*> IngredientItemHorizontalBoxs;
	TArray<IngredientItemData> Ingredients;

	int SelectedItemId;

	bool isManufacture;
};
