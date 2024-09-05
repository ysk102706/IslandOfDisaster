// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers.h"
#include "UIManager.h"
#include "DataLoadManager.h"
#include "DisasterManager.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "../Actor/Weather.h"
#include "../Actor/TimeOfDay.h"
#include "FXManager.h"
#include "SoundManager.h"

#define InitManager(Type) \
	if (Type##ManagerClass->StaticClass()) Type##ManagerObject = NewObject<U##Type##Manager>(this, Type##ManagerClass);\
	else Type##ManagerObject = Type##ManagerClass.GetDefaultObject();\

UManagers::UManagers() {
	UIManagerClass = UUIManager::StaticClass();
	DataLoadManagerClass = UDataLoadManager::StaticClass();
	DisasterManagerClass = UDisasterManager::StaticClass();
	FXManagerClass = UFXManager::StaticClass();
	SoundManagerClass = USoundManager::StaticClass();
}

UUIManager* UManagers::UI() {
	return UIManagerObject;
}

UDataLoadManager* UManagers::DataLoad()
{
	return DataLoadManagerObject;
}

UDisasterManager* UManagers::Disaster()
{
	return DisasterManagerObject;
}

UFXManager* UManagers::FX()
{
	return FXManagerObject;
}

USoundManager* UManagers::Sound()
{
	return SoundManagerObject;
}

UManagers* UManagers::Get(const UWorld* World)
{
	auto a = UGameplayStatics::GetGameInstance(World);
	return Cast<UManagers>(UGameplayStatics::GetGameInstance(World));
}

void UManagers::SetPlayer(ACPP_Player* Player)
{
	PlayerObject = Player;
}

TObjectPtr<ACPP_Player> UManagers::Player()
{
	return PlayerObject;
}

TObjectPtr<AWeather> UManagers::Weather()
{
	return WeatherObject;
}

TObjectPtr<ATimeOfDay> UManagers::TimeOfDay()
{
	return TimeOfDayObject;
}

void UManagers::InitManagers(const UWorld* World) {
	InitManager(UI);
	InitManager(DataLoad);
	InitManager(Disaster);
	InitManager(FX);
	InitManager(Sound);

	WeatherObject = Cast<AWeather>(UGameplayStatics::GetActorOfClass(GetWorld(), AWeather::StaticClass()));
	TimeOfDayObject = Cast<ATimeOfDay>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimeOfDay::StaticClass()));
}