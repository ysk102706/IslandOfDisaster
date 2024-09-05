// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Disaster.h"
#include "Epidemic.generated.h"

class AWaterBodyLake;

/**
 * 
 */
UCLASS()
class ISLANDOFDISASTER_API AEpidemic : public ADisaster
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void OpenLevelDisaster() override;

	virtual void Effect1() override;
	virtual void Effect2() override;
	virtual void Effect3() override;

	UPROPERTY(EditAnywhere, Category=Spawn)
	TArray<FVector> RottenFishSpawnPos;
	UPROPERTY(EditAnywhere, Category = Spawn)
	TSubclassOf<AActor> RottenFish;
	UPROPERTY(EditAnywhere, Category = Spawn)
	float SpawnRange;

	UPROPERTY(EditAnywhere, Category=Material)
	TArray<TObjectPtr<UMaterialInterface>> WaterMaterials;

private:
	TObjectPtr<AWaterBodyLake> WaterBodyLake;

};
