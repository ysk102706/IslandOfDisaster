// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HelpUI.generated.h"

/**
 * 
 */
UCLASS()
class ISLANDOFDISASTER_API UHelpUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void PrePage();
	UFUNCTION()
	void NextPage();
	UFUNCTION()
	void Close();

	UFUNCTION()
	void SetPage();
	UFUNCTION()
	void SetHelpImage();

	UPROPERTY(EditAnywhere, Category=Image)
	TArray<TObjectPtr<UTexture2D>> HelpImages;

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* IMG_Help;
	UPROPERTY(meta = (BindWidget))
	class UButton* BPre;
	UPROPERTY(meta = (BindWidget))
	class UButton* BNext;
	UPROPERTY(meta = (BindWidget))
	class UButton* BClose;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TPage;

	int CurPage;
	
};
