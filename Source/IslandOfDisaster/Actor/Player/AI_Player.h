// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AI_Player.generated.h"

/**
 * 
 */
UCLASS()
class ISLANDOFDISASTER_API UAI_Player : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UAI_Player();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=State)
	bool IsWalk;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	bool IsJumpStart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	bool IsJumping;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	bool IsJumpEnd;

};
