// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Player.h"
#include "CPP_Player.h"

UAI_Player::UAI_Player()
{
	IsWalk = false;
	IsJumpStart = false;
}

void UAI_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (auto* player = Cast<ACPP_Player>(GetOwningActor())) {
		IsWalk = (bool)player->GetVelocity().Length();

		IsJumpStart = player->IsJumpStart;
		IsJumping = player->IsJumping;
		IsJumpEnd = player->IsJumpEnd;
	}
}
