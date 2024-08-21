// Fill out your copyright notice in the Description page of Project Settings.


#include "TitlePawn.h"
#include "../../Manager/Managers.h"
#include "../../Manager/UImanager.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "../../UI/TitleUI.h"
#include "../../UI/HelpUI.h"
#include "Camera/CameraComponent.h"

ATitlePawn::ATitlePawn()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATitlePawn::BeginPlay()
{
	Super::BeginPlay();
	
	UManagers::Get(GetWorld())->InitManager(GetWorld());

	SetActorLocation(FVector(6460.0, -8610.0, 1210.0));
	FindComponentByClass<UCameraComponent>()->SetWorldRotation(FRotator(5, 62.5, 0));
	
	UManagers::Get(GetWorld())->UI()->ShowWidget(EWidgetType::Title);

	if (auto PlayerController = Cast<APlayerController>(GetController())) {
		if (auto SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			SubSystem->AddMappingContext(IMC_Title, 0);
		}
	}
}

void ATitlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATitlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC) {
		EIC->BindAction(IA_Pre, ETriggerEvent::Started, this, &ATitlePawn::Pre);
		EIC->BindAction(IA_Next, ETriggerEvent::Started, this, &ATitlePawn::Next);
		EIC->BindAction(IA_Close, ETriggerEvent::Started, this, &ATitlePawn::Close);
	}
}

void ATitlePawn::Pre(const FInputActionValue& Value)
{
	if (GetIsHelpOpen()) Cast<UHelpUI>(UManagers::Get(GetWorld())->UI()->GetWidget(EWidgetType::Help))->PrePage();
}

void ATitlePawn::Next(const FInputActionValue& Value)
{
	if (GetIsHelpOpen()) Cast<UHelpUI>(UManagers::Get(GetWorld())->UI()->GetWidget(EWidgetType::Help))->NextPage();
}

void ATitlePawn::Close(const FInputActionValue& Value)
{
	if (GetIsHelpOpen()) Cast<UHelpUI>(UManagers::Get(GetWorld())->UI()->GetWidget(EWidgetType::Help))->Close();
}

bool ATitlePawn::GetIsHelpOpen()
{
	return Cast<UTitleUI>(UManagers::Get(GetWorld())->UI()->GetWidget(EWidgetType::Title))->IsHelpOpen;
}
