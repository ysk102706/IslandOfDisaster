// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void USoundManager::Init(const UWorld* World)
{
	AC_Wind = UGameplayStatics::SpawnSound2D(World, S_Wind);
	AC_Rain = UGameplayStatics::SpawnSound2D(World, S_Rain);

	AC_Wind->SetActive(false);
	AC_Rain->SetActive(false);
}

TObjectPtr<USoundBase> USoundManager::GetSound(ESound Type)
{
	TObjectPtr<USoundBase> Sound = nullptr;

	switch (Type) {
	case ESound::S_Construct: Sound = S_Construct;
		break;
	case ESound::S_Manufacture: Sound = S_Manufacture;
		break;
	case ESound::S_Earthquake: Sound = S_Earthquake;
		break;
	case ESound::S_Drink: Sound = S_Drink;
		break;
	case ESound::S_Eat: Sound = S_Eat;
		break;
	case ESound::S_SignalFlare: Sound = S_SignalFlare;
		break;
	}

	return Sound;
}

TObjectPtr<UAudioComponent> USoundManager::GetAudioComponent(ESound Type)
{
	TObjectPtr<UAudioComponent> AC = nullptr;

	switch (Type) {
	case ESound::S_Wind: AC = AC_Wind;
		break;
	case ESound::S_Rain: AC = AC_Rain;
		break;
	}

	return AC;
}

void USoundManager::PlaySingleSound(const UWorld* World, ESound Type)
{
	UGameplayStatics::SpawnSound2D(World, GetSound(Type));
}

void USoundManager::PlayLoopSound(ESound Type)
{
	GetAudioComponent(Type)->SetActive(true);
}

void USoundManager::StopLoopSound(ESound Type)
{
	GetAudioComponent(Type)->SetActive(false);
}

void USoundManager::SetSoundVolume(ESound Type, int Volume)
{
	GetAudioComponent(Type)->SetVolumeMultiplier(Volume * 0.33f);
}
