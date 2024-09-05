// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "../../Manager/Managers.h"
#include "../../Manager/FXManager.h"
#include "../TimeOfDay.h"
#include "Kismet/GameplayStatics.h"

void AAsteroid::OpenLevelDisaster()
{
	UGameplayStatics::OpenLevel(this, TEXT("Asteroid"));
}

void AAsteroid::Effect1()
{
	Super::Effect1();

	if (IsChangeDay) IsLight = false;
	
	if (Hours == 1) UManagers::Get(GetWorld())->FX()->SpawnFX(GetWorld(), EFXType::FX_Asteroid, FVector(50000, 50000, 75000));
}

void AAsteroid::Effect2()
{
	int Hour = (Hours + 9) % 24;
	if (Hour == 21 && Random(0, 1)) UManagers::Get(GetWorld())->FX()->SetActiveFX(GetWorld(), EFXType::FX_ShootingStar, true);
	else if (Hour == 6) UManagers::Get(GetWorld())->FX()->SetActiveFX(GetWorld(), EFXType::FX_ShootingStar, false);
}

void AAsteroid::Effect3()
{
	int Hour = (Hours + 9) % 24;
	if ((Hour >= 20 || Hour <= 5) && !IsLight) {
		int Value = Random(1, 5);
		if (Value == 1) {
			UManagers::Get(GetWorld())->TimeOfDay()->NightLighting();
			IsLight = true;
		}
	}

	IsChangeDay = false;
}