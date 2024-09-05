// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SoundManager.generated.h"

UENUM(BlueprintType)
enum ESound {
	S_Construct UMETA(DisplayName = "Construct"),
	S_Manufacture UMETA(DisplayName = "Manufacture"),
	S_Wind UMETA(DisplayName = "Wind"),
	S_Rain UMETA(DisplayName = "Rain"),
	S_Earthquake UMETA(DisplayName = "Earthquake"),
	S_Drink UMETA(DisplayName = "Drink"),
	S_Eat UMETA(DisplayName = "Eat"),
	S_SignalFlare UMETA(DisplayName = "SignalFlare")
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ISLANDOFDISASTER_API USoundManager : public UObject
{
	GENERATED_BODY()

public:
	void Init(const UWorld* World);

	TObjectPtr<USoundBase> GetSound(ESound Type);
	TObjectPtr<UAudioComponent> GetAudioComponent(ESound Type);

	void PlaySingleSound(const UWorld* World, ESound Type);
	void PlayLoopSound(ESound Type);
	void StopLoopSound(ESound Type);

	void SetSoundVolume(ESound Type, int Volume);

	UPROPERTY(EditAnywhere, Category = Sound)
	TObjectPtr<USoundBase> S_Construct;
	UPROPERTY(EditAnywhere, Category = Sound)
	TObjectPtr<USoundBase> S_Manufacture;
	UPROPERTY(EditAnywhere, Category = Sound)
	TObjectPtr<USoundBase> S_Wind;
	UPROPERTY(EditAnywhere, Category = Sound)
	TObjectPtr<USoundBase> S_Rain;
	UPROPERTY(EditAnywhere, Category = Sound)
	TObjectPtr<USoundBase> S_Earthquake;
	UPROPERTY(EditAnywhere, Category = Sound)
	TObjectPtr<USoundBase> S_Drink;
	UPROPERTY(EditAnywhere, Category = Sound)
	TObjectPtr<USoundBase> S_Eat;
	UPROPERTY(EditAnywhere, Category = Sound)
	TObjectPtr<USoundBase> S_SignalFlare;

private:
	UPROPERTY()
	TObjectPtr<UAudioComponent> AC_Wind;
	UPROPERTY()
	TObjectPtr<UAudioComponent> AC_Rain;
	
};
