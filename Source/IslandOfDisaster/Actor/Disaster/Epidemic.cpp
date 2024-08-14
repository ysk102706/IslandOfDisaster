// Fill out your copyright notice in the Description page of Project Settings.


#include "Epidemic.h"
#include "WaterBodyLakeActor.h"
#include "EngineUtils.h"
#include "Materials/MaterialInstance.h"

void AEpidemic::BeginPlay()
{
	Super::BeginPlay();

	
	WaterBodyLake = *TActorIterator<AWaterBodyLake> (GetWorld());
	WaterBodyLake->SetWaterMaterial(WaterMaterials[Hours / 24]);
}

void AEpidemic::Effect1()
{
	Super::Effect1();

	if (IsChangeDay) AnimalEpidemicPercent = Random(2, 6);
}

void AEpidemic::Effect2()
{
	if (IsChangeDay) {
		WaterBodyLake->GetWaterBodyComponent()->SetVisibility(false);
		WaterBodyLake->SetWaterMaterial(WaterMaterials[Hours / 24]);
		WaterBodyLake->GetWaterBodyComponent()->SetVisibility(true);
	}
}

void AEpidemic::Effect3()
{
	if (!(Hours % 48)) {
		FVector SpawnPos = RottenFishSpawnPos[Random(0, RottenFishSpawnPos.Num() - 1)];
		int SpawnCount = Random(3, 7);

		for (int i = 0; i < SpawnCount; i++) {
			FVector Position = RandomCircle(SpawnPos, 200);
			FRotator Rotation = FRotator(0, Random(0, 360), 0);

			GetWorld()->SpawnActor(RottenFish, &Position, &Rotation);
			GetWorld()->SpawnActor(RottenFish, &Position, &Rotation);
		} 
	}

	IsChangeDay = false;
}
