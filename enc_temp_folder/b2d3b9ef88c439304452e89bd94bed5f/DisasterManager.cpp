// Fill out your copyright notice in the Description page of Project Settings.


#include "DisasterManager.h"
#include "../Actor/Disaster/Disaster.h"
#include "Kismet/GameplayStatics.h"

void UDisasterManager::SetDisaster(EDisasterType Type)
{
	ADisaster* SelectedDisaster = nullptr;
	FVector Pos = FVector(0, 0, 0);
	FRotator Rot = FRotator(0, 0, 0);

	switch (Type) {
	case EDisasterType::Tsunami:
		SelectedDisaster = Cast<ADisaster>(GetWorld()->SpawnActor(Tsunami, &Pos, &Rot));
		break;
	case EDisasterType::Volcano:
		SelectedDisaster = Cast<ADisaster>(GetWorld()->SpawnActor(Volcano, &Pos, &Rot));
		break;
	case EDisasterType::Epidemic:
		SelectedDisaster = Cast<ADisaster>(GetWorld()->SpawnActor(Epidemic, &Pos, &Rot));
		break;
	case EDisasterType::Asteroid:
		SelectedDisaster = Cast<ADisaster>(GetWorld()->SpawnActor(Asteroid, &Pos, &Rot));
		break;
	case EDisasterType::Typhoon:
		SelectedDisaster = Cast<ADisaster>(GetWorld()->SpawnActor(Typhoon, &Pos, &Rot));
		break;
	}

	Disaster = SelectedDisaster;
	DisasterType = Type;
}

void UDisasterManager::StartCutScene()
{
	switch (DisasterType) {
	case EDisasterType::Tsunami:
		UGameplayStatics::OpenLevel(this, TEXT("Tsunami"));
		break;
	case EDisasterType::Volcano:
		UGameplayStatics::OpenLevel(this, TEXT("Volcano"));
		break;
	case EDisasterType::Epidemic:
		UGameplayStatics::OpenLevel(this, TEXT("Epidemic"));
		break;
	case EDisasterType::Asteroid:
		UGameplayStatics::OpenLevel(this, TEXT("Asteroid"));
		break;
	case EDisasterType::Typhoon:
		UGameplayStatics::OpenLevel(this, TEXT("Typhoon"));
		break;
	}
}
