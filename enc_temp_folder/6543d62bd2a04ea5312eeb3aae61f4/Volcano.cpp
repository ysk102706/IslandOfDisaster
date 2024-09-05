// Fill out your copyright notice in the Description page of Project Settings.


#include "Volcano.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/CPP_PlayerState.h"
#include "../../Manager/Managers.h"
#include "../Player/CPP_Player.h"
#include "../../Manager/FXManager.h"

void AVolcano::BeginPlay()
{
	Super::BeginPlay();

	PosCnt = SmokeSpawnPos.Num() - 1;
	SpawnCnt = 0;

	Init(0, PosCnt, 1);
}

void AVolcano::Effect1()
{
	Super::Effect1();

	if (!(Hours % 6)) UManagers::Get(GetWorld())->Player()->Shake();
}

void AVolcano::Effect2()
{
	if (IsChangeDay) Cast<ACPP_PlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0))->ChangeAdditionalTemperature();
}

void AVolcano::Effect3()
{
	if (IsChangeDay) {
		int Idx = Random(1, SmokeSpawnPos.Num() - SpawnCnt);
		UE_LOG(LogTemp, Warning, TEXT("p : %d"), Idx);
		Idx = Query(0, PosCnt, 1, Idx);
		Update(0, PosCnt, 1, Idx);

		UE_LOG(LogTemp, Warning, TEXT("a : %d"), Idx);

		IsSpawned[Idx] = 1;
		FVector SpawnPos = SmokeSpawnPos[Idx];

		UManagers::Get(GetWorld())->FX()->SpawnFX(GetWorld(), EFXType::FX_Gas, SpawnPos);

		SpawnCnt++;
	}

	IsChangeDay = false;
}