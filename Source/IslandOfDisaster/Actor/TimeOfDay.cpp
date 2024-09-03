// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeOfDay.h"
#include "EngineUtils.h"
#include "Engine/DirectionalLight.h"
#include "Components/LightComponent.h"
#include "Components/DirectionalLightComponent.h"
#include "Engine/PostProcessVolume.h"
#include "../Manager/Managers.h"
#include "Weather.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "../Manager/FXManager.h"

ATimeOfDay::ATimeOfDay()
{
	PrimaryActorTick.bCanEverTick = true;

	IsLighting = false;
	LightingTimer = 0;
}

void ATimeOfDay::BeginPlay()
{
	Super::BeginPlay();

	TActorIterator<ADirectionalLight> It(GetWorld());
	while ((*It)->ActorHasTag("SunLight")) ++It;

	SunLight = *It;
	++It;
	MoonLight = *It;

	PostProcessVolume = *TActorIterator<APostProcessVolume>(GetWorld());

	SM_Center = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Center")));
	SM_Moon = Cast<UStaticMeshComponent>(SM_Center->GetChildComponent(0));
}

void ATimeOfDay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLighting) {
		LightingTimer += DeltaTime;
		if (LightingTimer >= 1.5f) {
			IsLighting = false;
			PostProcessVolume->Settings.AutoExposureBias = -1;
			LightingTimer = 0;
		}
	}

}

void ATimeOfDay::TimeToSunRotation(int Hours, int Minutes)
{
	if (Hours == 6) {
		SunLight->GetLightComponent()->bAffectsWorld = true;
		MoonLight->GetLightComponent()->bAffectsWorld = false;

		if (!UManagers::Get(GetWorld())->Weather()->IsRain) PostProcessVolume->Settings.AutoExposureBias = 1;

		ReRender(*(SunLight->GetLightComponent()));
		ReRender(*(MoonLight->GetLightComponent()));

		UManagers::Get(GetWorld())->FX()->SetActiveFX(GetWorld(), EFXType::FX_Star, false);
	}
	else if (Hours == 18 && Minutes == 15) {
		SunLight->GetLightComponent()->bAffectsWorld = false;
		MoonLight->GetLightComponent()->bAffectsWorld = true;

		PostProcessVolume->Settings.AutoExposureBias = -1;

		ReRender(*(SunLight->GetLightComponent()));
		ReRender(*(MoonLight->GetLightComponent()));

		UManagers::Get(GetWorld())->FX()->SetActiveFX(GetWorld(), EFXType::FX_Star, true);
	}

	SunLight->SetActorRotation(FRotator((Hours - 6) * -15 + Minutes * -0.25f, 0, 0));
	SM_Center->SetWorldRotation(FRotator(0, 90, (Hours - 6) * -15 + Minutes * -0.25f + 180));
}

void ATimeOfDay::NightLighting()
{
	IsLighting = true;
	PostProcessVolume->Settings.AutoExposureBias = 2;
}

void ATimeOfDay::ReRender(ULightComponent& Component)
{
	Component.SetVisibility(false);
	Component.SetVisibility(true);
}