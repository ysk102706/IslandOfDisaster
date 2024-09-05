// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FXManager.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UENUM(BlueprintType)
enum EFXType {
	FX_Asteroid		UMETA(DisplayName = "FX_Asteroid"),
	FX_Gas			UMETA(DisplayName = "Gas"),
	FX_Rain			UMETA(DisplayName = "Rain"),
	FX_ShootingStar	UMETA(DisplayName = "ShootingStar"),
	FX_Star			UMETA(DisplayName = "Star"),
	FX_Wind			UMETA(DisplayName = "Wind")
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ISLANDOFDISASTER_API UFXManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Tick(const UWorld* World);

	TObjectPtr<UNiagaraSystem> GetFX(EFXType Type);
	void SetComponent(EFXType Type, TObjectPtr<UNiagaraComponent> Component);
	TObjectPtr<UNiagaraComponent> GetComponent(EFXType Type);
	
	void SpawnFX(const UWorld* World, EFXType Type, FVector Pos);
	void SetActiveFX(const UWorld* World, EFXType Type, bool Value);


	UPROPERTY(EditAnywhere, Category=FX)
	TObjectPtr<UNiagaraSystem> NS_Asteroid;
	UPROPERTY(EditAnywhere, Category=FX)
	TObjectPtr<UNiagaraSystem> NS_Gas;
	UPROPERTY(EditAnywhere, Category=FX)
	TObjectPtr<UNiagaraSystem> NS_Rain;
	UPROPERTY(EditAnywhere, Category=FX)
	TObjectPtr<UNiagaraSystem> NS_ShootingStar;
	UPROPERTY(EditAnywhere, Category=FX)
	TObjectPtr<UNiagaraSystem> NS_Star;
	UPROPERTY(EditAnywhere, Category=FX)
	TObjectPtr<UNiagaraSystem> NS_Wind;

private:
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NSC_Rain;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NSC_ShootingStar;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NSC_Star;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> NSC_Wind;

};
