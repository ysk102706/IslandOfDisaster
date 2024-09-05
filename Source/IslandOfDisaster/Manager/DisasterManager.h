// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DisasterManager.generated.h"

class ADisaster;

UENUM(BlueprintType)
enum EDisasterType {
	Tsunami		UMETA(DisplayName="Tsunami"),
	Volcano		UMETA(DisplayName="Volcano"),
	Epidemic	UMETA(DisplayName="Epidemic"),
	Asteroid	UMETA(DisplayName="Asteroid"),
	Typhoon		UMETA(DisplayName="Typhoon")
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ISLANDOFDISASTER_API UDisasterManager : public UObject
{
	GENERATED_BODY()
	
public:
	void SetDisaster(EDisasterType Type);

	UPROPERTY(EditAnywhere, Category = Disaster)
	TSubclassOf<ADisaster> Tsunami;
	UPROPERTY(EditAnywhere, Category = Disaster)
	TSubclassOf<ADisaster> Volcano;
	UPROPERTY(EditAnywhere, Category = Disaster)
	TSubclassOf<ADisaster> Epidemic;
	UPROPERTY(EditAnywhere, Category = Disaster)
	TSubclassOf<ADisaster> Asteroid;
	UPROPERTY(EditAnywhere, Category = Disaster)
	TSubclassOf<ADisaster> Typhoon;

	UPROPERTY()
	ADisaster* Disaster;
	EDisasterType DisasterType;

};
