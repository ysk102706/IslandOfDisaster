// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IslandOfDisasterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ISLANDOFDISASTER_API AIslandOfDisasterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AIslandOfDisasterGameModeBase();
	virtual void BeginPlay() override;
};
