// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleUI.generated.h"

/**
 * 
 */
UCLASS()
class ISLANDOFDISASTER_API UTitleUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void Start();
	UFUNCTION()
	void Help();
	UFUNCTION()
	void Quit();

	bool IsHelpOpen;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* BStart;
	UPROPERTY(meta = (BindWidget))
	class UButton* BHelp;
	UPROPERTY(meta = (BindWidget))
	class UButton* BQuit;

};
