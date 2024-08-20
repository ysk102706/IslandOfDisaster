// Fill out your copyright notice in the Description page of Project Settings.


#include "TitlePawn.h"
#include "../../Manager/Managers.h"
#include "../../Manager/UImanager.h"

ATitlePawn::ATitlePawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATitlePawn::BeginPlay()
{
	Super::BeginPlay();
	
	UManagers::Get(GetWorld())->InitManager(GetWorld());

	SetActorLocation(FVector(6460.0, -8610.0, 1210.0));
	SetActorRotation(FRotator(5, 62.5, 0));
	
	UManagers::Get(GetWorld())->UI()->ShowWidget(EWidgetType::Title);
}

void ATitlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}