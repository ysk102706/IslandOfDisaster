// Fill out your copyright notice in the Description page of Project Settings.


#include "Typhoon.h"
#include "Kismet/GameplayStatics.h"
#include "../Player/CPP_PlayerState.h"
#include "../../Manager/Managers.h"
#include "../Weather.h"
#include "../../Manager/FXManager.h"
#include "../../Manager/SoundManager.h"

void ATyphoon::OpenLevelDisaster()
{
	UGameplayStatics::OpenLevel(this, TEXT("Typhoon"));
}

void ATyphoon::Effect1()
{
	Super::Effect1();

	if (IsChangeDay) {
		int Value = Random(1, 100);
		if (Value <= DarkPercent) UManagers::Get(GetWorld())->Weather()->Dark(); 
		else UManagers::Get(GetWorld())->Weather()->Clear();

		DarkPercent += 15;
	}
}

void ATyphoon::Effect2()
{
	if (IsChangeDay) Cast<ACPP_PlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0))->ChangeAdditionalHumidity();
}

void ATyphoon::Effect3()
{
	if (Hours == 24) {
		UManagers::Get(GetWorld())->FX()->SpawnFX(GetWorld(), EFXType::FX_Wind, FVector(0, 0, 0));
		UManagers::Get(GetWorld())->Sound()->PlayLoopSound(ESound::S_Wind);
	}

	if (IsChangeDay) {
		WindSoundVolume++;
		UManagers::Get(GetWorld())->Sound()->SetSoundVolume(ESound::S_Wind, WindSoundVolume);
	}

	IsChangeDay = false;
}
