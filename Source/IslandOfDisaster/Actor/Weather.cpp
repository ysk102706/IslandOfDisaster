// Fill out your copyright notice in the Description page of Project Settings.


#include "Weather.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Engine/PostProcessVolume.h"
#include "Components/VolumetricCloudComponent.h"
#include "EngineUtils.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "../Manager/Managers.h"
#include "Player/CPP_Player.h"

AWeather::AWeather()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeather::BeginPlay()
{
	Super::BeginPlay();
	  
	SkyAtmosphere = *TActorIterator<ASkyAtmosphere>(GetWorld());
	PostProcessVolume = *TActorIterator<APostProcessVolume> (GetWorld());
	VolumetricCloud = *TActorIterator<AVolumetricCloud>(GetWorld());

	PostProcessVolume->Settings.bOverride_AutoExposureBias = true;

	DMI = UMaterialInstanceDynamic::Create(M_Cloud, this);
	VolumetricCloud->FindComponentByClass<UVolumetricCloudComponent>()->SetMaterial(DMI);

	CurrentRayleighScattering = FLinearColor(0.175287f, 0.409607f, 1);
	CurrentExposureCompensationValue = 1;
	CurrentDensityOffset = 0;
}

void AWeather::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLerp) {
		LerpRatio += DeltaTime * 0.04f;

		SetRayleighScattering(LerpColor(CurrentRayleighScattering, TargetRayleighScattering, LerpRatio));
		SetExposureCompensation(Lerp(CurrentExposureCompensationValue, TargetExposureCompensationValue, LerpRatio));
		SetDensityOffset(Lerp(CurrentDensityOffset, TargetDensityOffset, LerpRatio));

		if (IsRainClear && LerpRatio >= 0.6f) {
			//UManagers::Get(GetWorld())->Player()->SetActiveRain(false);
			
			IsRainClear = false;
			IsRain = false;
		}

		if (LerpRatio >= 1) {
			CurrentRayleighScattering = TargetRayleighScattering;
			CurrentExposureCompensationValue = TargetExposureCompensationValue;
			CurrentDensityOffset = TargetDensityOffset;

			IsLerp = false;

			//if (IsRain) UManagers::Get(GetWorld())->Player()->SetActiveRain(true);
		}
	}
}

void AWeather::Dark()
{   
	TargetRayleighScattering = FLinearColor(1, 1, 1);
	TargetExposureCompensationValue = -1;
	TargetDensityOffset = 0.5f;

	LerpRatio = 0;
	IsLerp = true;
}

void AWeather::Clear()
{
	TargetRayleighScattering = FLinearColor(0.175287f, 0.409607f, 1);
	TargetExposureCompensationValue = 1;
	TargetDensityOffset = 0;

	LerpRatio = 0;
	IsLerp = true;

	if (IsRain) IsRainClear = true;
}

void AWeather::Rain()
{
	Dark();

	IsRain = true;
}

void AWeather::SetRayleighScattering(FLinearColor Color)
{
	SkyAtmosphere->GetComponent()->SetRayleighScattering(Color);
}

void AWeather::SetExposureCompensation(float Value)
{
	PostProcessVolume->Settings.AutoExposureBias = Value;
}

void AWeather::SetDensityOffset(float Value)
{
	DMI->SetScalarParameterValue("DensityOffset", Value);
}

float AWeather::Lerp(float StartValue, float TargetValue, float Ratio)
{
	return StartValue + (TargetValue - StartValue) * FMath::Min(Ratio, 1);
}

FLinearColor AWeather::LerpColor(FLinearColor StartValue, FLinearColor TargetValue, float Ratio)
{
	return FLinearColor(Lerp(StartValue.R, TargetValue.R, Ratio), Lerp(StartValue.G, TargetValue.G, Ratio), Lerp(StartValue.B, TargetValue.B, Ratio));
}

