// Fill out your copyright notice in the Description page of Project Settings.


#include "Tsunami.h"

void ATsunami::Effect1()
{
	Super::Effect1();

	if (!(Hours % 48)) {
		FVector SpawnPos = FishSpawnPos[Random(0, FishSpawnPos.Num() - 1)];
		int SpawnCount = Random(3, 7);

		for (int i = 0; i < SpawnCount; i++) {
			FVector Position = RandomCircle(SpawnPos, 200);
			FRotator Rotation = FRotator(0, Random(0, 360), 0);

			GetWorld()->SpawnActor(Fish, &Position, &Rotation);
			GetWorld()->SpawnActor(Fish, &Position, &Rotation);
		}
	}
}

void ATsunami::Effect2()
{
	if (!(Hours % 5)) 1;
}

void ATsunami::Effect3()
{
	if (IsChangeDay) 1;

	IsChangeDay = false;
}
