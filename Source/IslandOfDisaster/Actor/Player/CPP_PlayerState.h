// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CPP_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ISLANDOFDISASTER_API ACPP_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	void Spawns();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void Initialize();
	int Random(int MinInclusive, int MaxInclusive);
	
	void StartTimer();
	void StateApplyToUI();

	void IncreaseHP(float Value);
	void IncreaseHunger(float Value);
	void IncreaseThirsty(float Value);
	void IncreaseTemperature(float Value);
	void IncreaseHumidity(float Value);

	void DecreaseHP(float Value);
	void DecreaseHunger(float Value);
	void DecreaseThirsty(float Value);
	void DecreaseTemperature(float Value);
	void DecreaseHumidity(float Value);

	void ChangeTemperature();
	void ChangeHumidity();

	void ChangeAdditionalTemperature();
	void ChangeAdditionalHumidity();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)
	float CurHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)
	float CurHunger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)
	float MaxHunger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)
	float CurThirsty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)
	float MaxThirsty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)
	float MaxTemperature;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info)
	float MaxHumidity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Times)
	float RealTimeSecondToInGameHour;

	float CurTemperature;
	float CurHumidity;
	
	bool isOnTimer;
	float Timer;
	
	int Days;
	int Hours;

	int PhysiologicalPhenomenonUnit;
	int TemperatureAndHumidityUnit;

	int AdditionalTemperature;
	int AdditionalHumidity;

	TArray<TObjectPtr<class ASpawner>> Spawners;

	TObjectPtr<class ADisaster> Disaster;
	
};
