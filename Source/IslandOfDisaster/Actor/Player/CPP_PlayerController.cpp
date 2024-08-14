// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerController.h"

void ACPP_PlayerController::BeginPlay() {
	bEnableClickEvents = true;
}

void ACPP_PlayerController::SetCursorVisibility(bool Visibility) {
	bShowMouseCursor = Visibility;
}