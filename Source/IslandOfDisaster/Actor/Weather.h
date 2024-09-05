// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weather.generated.h"

UCLASS()
class ISLANDOFDISASTER_API AWeather : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeather();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Dark();
	void Clear();
	void Rain();

	UPROPERTY(EditANywhere, Category=Material)
	TObjectPtr<UMaterialInterface> M_Cloud;

	bool IsRain;

private: 
	void SetRayleighScattering(FLinearColor Color);
	void SetExposureCompensation(float Value);
	void SetDensityOffset(float Value);

	float Lerp(float StartValue, float TargetValue, float Ratio);
	FLinearColor LerpColor(FLinearColor StartValue, FLinearColor TargetValue, float Ratio);

	UPROPERTY()
	TObjectPtr<class ASkyAtmosphere> SkyAtmosphere;
	UPROPERTY()
	TObjectPtr<class APostProcessVolume> PostProcessVolume;
	UPROPERTY()
	TObjectPtr<class AVolumetricCloud> VolumetricCloud;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DMI;

	UPROPERTY()
	FLinearColor CurrentRayleighScattering;
	UPROPERTY()
	FLinearColor TargetRayleighScattering;

	float CurrentExposureCompensationValue;
	float TargetExposureCompensationValue;

	float CurrentDensityOffset;
	float TargetDensityOffset;

	bool IsLerp;
	float LerpRatio;

	bool IsRainClear;
};
