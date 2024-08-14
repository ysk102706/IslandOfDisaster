// Copyright Epic Games, Inc. All Rights Reserved.


#include "IslandOfDisasterGameModeBase.h"
#include "Actor/Player/CPP_Player.h"
#include "Actor/Player/CPP_PlayerState.h"
#include "Manager/Managers.h"
#include "Kismet/GameplayStatics.h"

AIslandOfDisasterGameModeBase::AIslandOfDisasterGameModeBase()
{
	DefaultPawnClass = ACPP_Player::StaticClass();
	PlayerStateClass = ACPP_PlayerState::StaticClass();
}

void AIslandOfDisasterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UManagers::Get(GetWorld())->InitManager(GetWorld());
}
