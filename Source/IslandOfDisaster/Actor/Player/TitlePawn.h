// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TitlePawn.generated.h"

UCLASS()
class ISLANDOFDISASTER_API ATitlePawn : public APawn
{
	GENERATED_BODY()

public:
	ATitlePawn();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
