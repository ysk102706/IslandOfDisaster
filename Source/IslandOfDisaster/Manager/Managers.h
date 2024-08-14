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

/**
 * 
 */
UCLASS()
class ISLANDOFDISASTER_API UManagers : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UManagers();
	void InitManager(const UWorld* World);
	
	UUIManager* UI();
	UDataLoadManager* DataLoad();
	UDisasterManager* Disaster();
	UFXManager* FX();

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
	
	TObjectPtr<UUIManager> UIManagerObject;
	TObjectPtr<UDataLoadManager> DataLoadManagerObject;
	TObjectPtr<UDisasterManager> DisasterManagerObject;
	TObjectPtr<UFXManager> FXManagerObject;
	TObjectPtr<ACPP_Player> PlayerObject;

	TObjectPtr<AWeather> WeatherObject;
	TObjectPtr<ATimeOfDay> TimeOfDayObject;

};
