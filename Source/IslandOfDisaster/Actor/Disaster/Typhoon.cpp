// Fill out your copyright notice in the Description page of Project Settings.


#include "Typhoon.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/CPP_PlayerState.h"
#include "../../Manager/Managers.h"
#include "../Weather.h"

void ATyphoon::Effect1()
{
	Super::Effect1();

	if (!(Hours % 24)) {
		if (Hours / 24 % 2) UManagers::Get(GetWorld())->Weather()->Rain(); 
		else UManagers::Get(GetWorld())->Weather()->Clear();
	}
}

void ATyphoon::Effect2()
{
	if (IsChangeDay) Cast<ACPP_PlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0))->ChangeAdditionalHumidity();
}

void ATyphoon::Effect3()
{
	if (IsChangeDay) WindSoundVolume++;

	IsChangeDay = false;
}
