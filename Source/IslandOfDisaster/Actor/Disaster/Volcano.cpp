// Fill out your copyright notice in the Description page of Project Settings.


#include "Volcano.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/CPP_PlayerState.h"

void AVolcano::Effect1()
{
	Super::Effect1();

	if (!(Hours % 6)) 1;
}

void AVolcano::Effect2()
{
	if (IsChangeDay) Cast<ACPP_PlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0))->ChangeAdditionalTemperature();
}

void AVolcano::Effect3()
{
	if (IsChangeDay) 1;

	IsChangeDay = false;
}
