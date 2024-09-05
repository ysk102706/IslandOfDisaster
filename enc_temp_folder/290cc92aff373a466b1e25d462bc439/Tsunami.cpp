// Fill out your copyright notice in the Description page of Project Settings.


#include "Tsunami.h"
#include "../Player/CPP_Player.h"
#include "../../Manager/Managers.h"
#include "../Weather.h"

void ATsunami::Effect1()
{
	Super::Effect1();

	if (!(Hours % 48)) {
		FVector SpawnPos = FishSpawnPos[Random(0, FishSpawnPos.Num() - 1)];
		int SpawnCount = Random(3, 7);

		for (int i = 0; i < SpawnCount; i++) {
			FVector Position = RandomCircle(SpawnPos, SpawnRange);
			FRotator Rotation = FRotator(0, Random(0, 360), 0);

			GetWorld()->SpawnActor(Fish, &Position, &Rotation);
			GetWorld()->SpawnActor(Fish, &Position, &Rotation);
		}
	}
}

void ATsunami::Effect2()
{
	if (!(Hours % 5)) UManagers::Get(GetWorld())->Player()->Shake();
}

void ATsunami::Effect3()
{
	if (IsChangeDay) {
		int Value = Random(1, 100);

		if (Value <= 30) UManagers::Get(GetWorld())->Weather()->Rain();
		else UManagers::Get(GetWorld())->Weather()->Clear();
	}

	IsChangeDay = false;
}
