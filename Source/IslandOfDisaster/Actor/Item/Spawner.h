// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class AItem;

UCLASS()
class ISLANDOFDISASTER_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	void Spawn();
	int Random(int MinInclusive, int MaxInclusive);

	UPROPERTY(EditAnywhere, Category = Item)
	int Id;
	UPROPERTY(EditAnywhere, Category = Item)
	TArray<TSubclassOf<AActor>> MultiItems;

	UPROPERTY(EditAnywhere, Category = SpawnType)
	bool IsOnce;


	bool IsSpawned;
	TObjectPtr<AActor> SpawnedActor;

	bool IsOnceSpawn;
};