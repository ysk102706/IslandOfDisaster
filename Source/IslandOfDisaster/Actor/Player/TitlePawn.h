// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TitlePawn.generated.h"

UCLASS()
class ISLANDOFDISASTER_API ATitlePawn : public ACharacter
{
	GENERATED_BODY()

public:
	ATitlePawn();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Pre(const FInputActionValue& Value);
	UFUNCTION()
	void Next(const FInputActionValue& Value);
	UFUNCTION()
	void Close(const FInputActionValue& Value);

	bool GetIsHelpOpen();

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IMC_Title;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Pre;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Next;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Close;

};
