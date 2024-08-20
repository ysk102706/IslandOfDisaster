// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeOfDay.generated.h"

UCLASS()
class ISLANDOFDISASTER_API ATimeOfDay : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimeOfDay();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void TimeToSunRotation(int Hours, int Minutes);

	void ReRender(ULightComponent& Component);

	TObjectPtr<class ADirectionalLight> SunLight;
	TObjectPtr<class ADirectionalLight> MoonLight;

	TObjectPtr<class APostProcessVolume> PostProcessVolume;

	TObjectPtr<class UStaticMeshComponent> SM_Center;
	TObjectPtr<class UStaticMeshComponent> SM_Moon;
};
