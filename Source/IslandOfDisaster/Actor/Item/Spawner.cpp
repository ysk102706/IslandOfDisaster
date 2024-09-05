// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "../../Manager/Managers.h"
#include "../../Manager/DataLoadManager.h"
#include "Item.h"
#include <random>
#include "../../Manager/DisasterManager.h"
#include "../Disaster/Disaster.h"
#include "MultipleItem.h"

int ASpawner::Random(int MinInclusive, int MaxInclusive)
{
	std::random_device random;
	std::mt19937 engine(random());
	std::uniform_int_distribution<int> distribution(MinInclusive, MaxInclusive);
	return distribution(engine);
}

void ASpawner::Spawn()
{
	if (IsOnce && IsOnceSpawn) return;
	IsOnceSpawn = true;

	if (!IsSpawned) {
		if (Id >= 0) {
			SpawnedActor = UManagers::Get(GetWorld())->DataLoad()->SpawnItemActor(GetWorld(), Id);
			TObjectPtr<AItem> SpawnedItem = Cast<AItem>(SpawnedActor);
			SpawnedItem->SetActorLocation(GetActorLocation());
			SpawnedItem->SetWorldLocation(GetActorLocation());
			SpawnedItem->Spawner = this;
		}
		else {
			int Rand = Random(0, 10), Idx = Random(0, (MultiItems.Num() - 1) >> 1);

			if (!IsTree && Rand < UManagers::Get(GetWorld())->Disaster()->Disaster->AnimalEpidemicPercent) Idx += 4;

			FVector Pos = GetActorLocation();
			FRotator Rot = GetActorRotation();

			auto MultiItem = Cast<AMultipleItem>(GetWorld()->SpawnActor(MultiItems[Idx], &Pos, &Rot));

			MultiItem->Spawner = this;
			UManagers::Get(GetWorld())->SpawnedItems.Add(MultiItem);
		}
		IsSpawned = true;
	}
}
