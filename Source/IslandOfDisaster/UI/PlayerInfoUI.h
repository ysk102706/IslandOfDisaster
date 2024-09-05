// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInfoUI.generated.h"

/**
 * 
 */
UCLASS()
class ISLANDOFDISASTER_API UPlayerInfoUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void Init(int idx);
	UFUNCTION()
	void SetAllItem(UTexture2D* Texture);

	UFUNCTION()
	void SetHP(float MaxHP, float CurHP);
	UFUNCTION()
	void SetHunger(float MaxHunger, float CurHunger);
	UFUNCTION()
	void SetThirsty(float MaxThirsty, float CurThirsty);
	UFUNCTION()
	void SetTemperature(float MaxTemperature, float CurTemperature);
	UFUNCTION()
	void SetHumidity(float MaxHumidity, float CurHumidity);
	
	UFUNCTION()
	void SetDays(int Days);
	UFUNCTION()
	void SetHours(int Hours, int Minutes);

	UFUNCTION()
	void ChangeInventorySelectItem(int LastIdx, int Idx);
	UFUNCTION()
	void ChangeInventoryItemTexture(int Idx, UTexture2D* Texture);
	UFUNCTION()
	void ChangeInventoryItemCnt(int Idx, FString Text);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HPBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HungerBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ThirstyBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* TemperatureBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HumidityBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TDays;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* THours;

	UPROPERTY(meta = (BindWidget))
	class UImage* BG_Item1;
	UPROPERTY(meta = (BindWidget))
	class UImage* BG_Item2;
	UPROPERTY(meta = (BindWidget))
	class UImage* BG_Item3;
	UPROPERTY(meta = (BindWidget))
	class UImage* BG_Item4;
	UPROPERTY(meta = (BindWidget))
	class UImage* BG_Item5;
	UPROPERTY(meta = (BindWidget))
	class UImage* BG_Item6;
	UPROPERTY(meta = (BindWidget))
	class UImage* BG_Item7;

	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Item1;
	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Item2;
	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Item3;
	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Item4;
	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Item5;
	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Item6;
	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Item7;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CNT_Item1;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CNT_Item2;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CNT_Item3;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CNT_Item4;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CNT_Item5;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CNT_Item6;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CNT_Item7;

};
