// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Managers.generated.h"

class UUIManager; 
class UDataLoadManager;
class UDisasterManager;
class ACPP_Player;
class AWeather;
class ATimeOfDay;
class UFXManager;
class USoundManager;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ISLANDOFDISASTER_API UManagers : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UManagers();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "InitManger"))
	void InitManagers(const UWorld* World);
	
	UUIManager* UI();
	UDataLoadManager* DataLoad();
	UDisasterManager* Disaster();
	UFXManager* FX();
	USoundManager* Sound();

	void SetPlayer(ACPP_Player* Player);
	TObjectPtr<ACPP_Player> Player();
	
	TObjectPtr<AWeather> Weather();
	TObjectPtr<ATimeOfDay> TimeOfDay();

	static UManagers* Get(const UWorld* World);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUIManager> UIManagerClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDataLoadManager> DataLoadManagerClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDisasterManager> DisasterManagerClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UFXManager> FXManagerClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<USoundManager> SoundManagerClass;
	
	UPROPERTY()
	TObjectPtr<UUIManager> UIManagerObject;
	UPROPERTY()
	TObjectPtr<UDataLoadManager> DataLoadManagerObject;
	UPROPERTY()
	TObjectPtr<UDisasterManager> DisasterManagerObject;
	UPROPERTY()
	TObjectPtr<UFXManager> FXManagerObject;
	UPROPERTY()
	TObjectPtr<USoundManager> SoundManagerObject;
	UPROPERTY()
	TObjectPtr<ACPP_Player> PlayerObject;

	UPROPERTY()
	TObjectPtr<AWeather> WeatherObject;
	UPROPERTY()
	TObjectPtr<ATimeOfDay> TimeOfDayObject;

};
