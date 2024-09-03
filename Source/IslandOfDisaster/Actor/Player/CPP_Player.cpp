// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Player.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "Kismet/GameplayStatics.h"
#include "../../UI/PlayerInfoUI.h"
#include "../../Manager/Managers.h"
#include "../../Manager/UIManager.h"
#include "CPP_PlayerState.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "../../UI/ManufactureUI.h"
#include "CPP_PlayerController.h"
#include "../../Manager/DataLoadManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "LegacyCameraShake.h"
#include "../../Manager/FXManager.h"
#include "Components/CapsuleComponent.h"
#include "../Item/Item.h"
#include "../Item/MultipleItem.h"
#include "../Item/Inventory.h"
#include "../../Manager/SoundManager.h"
#include "../../UI/PlayerInfoUI.h"
#include "WaterBodyLakeComponent.h"
#include "WaterBodyOceanComponent.h"

ACPP_Player::ACPP_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	IsOpenManufacture = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetWorldRotation(FRotator::MakeFromEuler(FVector(0, -90, 0)));

	CaptureComp = CreateDefaultSubobject<USceneCaptureComponent2D>("CaptureComp");
	CaptureComp->SetupAttachment(SpringArm);
	CaptureComp->ProjectionType = ECameraProjectionMode::Orthographic;

	OnActorHit.AddDynamic(this, &ACPP_Player::OnHit);
}

void ACPP_Player::BeginPlay()
{
	Super::BeginPlay();

	UManagers::Get(GetWorld())->SetPlayer(this);

	SetActorLocation(FVector(62250.0, 40000.0, 990));

	Inventory = NewObject<AInventory>();
	Inventory->AddToRoot();

	Inventory->SetWorld(GetWorld());
	Inventory->SetNoneItemTexture(NoneItemTexture);
	Inventory->SelectItem(0);

	UManagers::Get(GetWorld())->DataLoad()->LoadManufacturedItemList(GetWorld());

	CQP.AddIgnoredActor(this->GetOwner());

	PlayerCamera = FindComponentByClass<UCameraComponent>();

	if (auto PlayerController = Cast<APlayerController>(GetController())) {
		if (auto SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			SubSystem->AddMappingContext(IMC_Default, 0);
		}
	}

	UManagers::Get(GetWorld())->UI()->ShowWidget(EWidgetType::PlayerInfo);
	Cast<UPlayerInfoUI>(UManagers::Get(GetWorld())->UI()->GetWidget(EWidgetType::PlayerInfo))->Init();
	Cast<UPlayerInfoUI>(UManagers::Get(GetWorld())->UI()->GetWidget(EWidgetType::PlayerInfo))->SetAllItem(NoneItemTexture);

	UManagers::Get(GetWorld())->FX()->SpawnFX(GetWorld(), EFXType::FX_Star, FVector(0, 0, 0));
	UManagers::Get(GetWorld())->FX()->SetActiveFX(GetWorld(), EFXType::FX_Star, false);

	JumpStartTimer = 0;
	JumpEndTimer = 0;

	UManagers::Get(GetWorld())->Sound()->Init(GetWorld());
}

void ACPP_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetController()->GetPlayerState<ACPP_PlayerState>()->Tick(DeltaTime);

	ConstructCheckRayCast();
	ItemCheckRayCast();
	DrinkCheckRayCast();
	MultipleItemCheckRayCast();

	InputManufactureDelayTimer += DeltaTime;

	UManagers::Get(GetWorld())->FX()->Tick(GetWorld()); 

	if (IsJumpStart) {
		JumpStartTimer += DeltaTime;
		if (JumpStartTimer >= 0.75f) {
			IsJumping = true;
			IsJumpStart = false;

			JumpStartTimer = 0;
		}
	}

	if (IsJumpEnd) {
		JumpEndTimer += DeltaTime;
		if (JumpEndTimer >= 0.15f) {
			IsJumpEnd = false;

			JumpEndTimer = 0;
		}
	}
}

void ACPP_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	auto EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC) {
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ACPP_Player::Move);
		EIC->BindAction(IA_Camera, ETriggerEvent::Triggered, this, &ACPP_Player::Camera);
		EIC->BindAction(IA_Pick, ETriggerEvent::Started, this, &ACPP_Player::PickItem);
		EIC->BindAction(IA_Drop, ETriggerEvent::Started, this, &ACPP_Player::DropItem);
		EIC->BindAction(IA_SelectItem, ETriggerEvent::Started, this, &ACPP_Player::SelectItem);
		EIC->BindAction(IA_Manufacture, ETriggerEvent::Started, this, &ACPP_Player::Manufacture);
		EIC->BindAction(IA_Construct, ETriggerEvent::Started, this, &ACPP_Player::Construct);
		EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACPP_Player::IF_Jump);
		EIC->BindAction(IA_Drink, ETriggerEvent::Started, this, &ACPP_Player::Drink);
		EIC->BindAction(IA_Eat, ETriggerEvent::Started, this, &ACPP_Player::Eat);
		EIC->BindAction(IA_Escape, ETriggerEvent::Started, this, &ACPP_Player::Escape);
	}
}

void ACPP_Player::Move(const FInputActionValue& Value)
{
	if (!IsOpenManufacture) {
		FVector f_dir = GetForwardVector();
		FVector r_dir = GetForwardVector().Cross(FVector(0, 0, -1));
		AddMovementInput(f_dir, Value.Get<FVector2D>().X * 3);
		AddMovementInput(r_dir, Value.Get<FVector2D>().Y * 3);
	}
}

void ACPP_Player::Camera(const FInputActionValue& Value)
{
	if (!IsOpenManufacture) {
		AddControllerYawInput(Value.Get<FVector2D>().X);
		AddControllerPitchInput(Value.Get<FVector2D>().Y);
	}
}

void ACPP_Player::PickItem(const FInputActionValue& Value)
{
	if (FocusedItem) FocusedItem->Picked();
	if (FocusedMultipleItem) FocusedMultipleItem->Picked();
}

void ACPP_Player::DropItem(const FInputActionValue& Value)
{
	Inventory->DropItem();
}

void ACPP_Player::SelectItem(const FInputActionValue& Value)
{
	Inventory->SelectItem(Value.Get<float>());
}

void ACPP_Player::Manufacture(const FInputActionValue& Value)
{
	if (InputManufactureDelayTimer >= 0.2f) {
		InputManufactureDelayTimer = 0;

		IsOpenManufacture = !IsOpenManufacture;
		if (IsOpenManufacture) {
			UManagers::Get(GetWorld())->UI()->ShowWidget(EWidgetType::Manufacture);
			UManagers::Get(GetWorld())->DataLoad()->LoadSelectedManufacturedItem(GetWorld(), 1);
			UManagers::Get(GetWorld())->DataLoad()->LoadIngredientItems(GetWorld(), 1);
		}
		else UManagers::Get(GetWorld())->UI()->HideWidget(EWidgetType::Manufacture);
		Cast<ACPP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetCursorVisibility(IsOpenManufacture);
	}
}

void ACPP_Player::Construct(const FInputActionValue& Value)
{
	if (IsConstruct) {
		Inventory->ConstructItem();
		UManagers::Get(GetWorld())->Sound()->PlaySingleSound(GetWorld(), ESound::S_Construct);
	}
}

void ACPP_Player::IF_Jump(const FInputActionValue& Value)
{
	if (!IsJumpStart && !IsJumping && !IsJumpEnd) {
		Jump();

		IsJumpStart = true;
	}
}

void ACPP_Player::Drink(const FInputActionValue& Value)
{
	if (IsDrinkable) {
		Cast<ACPP_PlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0))->IncreaseThirsty(10);
		UManagers::Get(GetWorld())->Sound()->PlaySingleSound(GetWorld(), ESound::S_Drink);
	}
}

void ACPP_Player::Eat(const FInputActionValue& Value)
{
	if (Inventory->GetSelectedItem() && Inventory->GetSelectedItem()->Name == TEXT("고기")) {
		Inventory->Consume(TEXT("고기"), 1);
		Cast<ACPP_PlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0))->IncreaseHunger(10);
		UManagers::Get(GetWorld())->Sound()->PlaySingleSound(GetWorld(), ESound::S_Eat);
	}
}

void ACPP_Player::Escape(const FInputActionValue& Value)
{
	EEscapeType Type = EEscapeType::None;

	if (Inventory->GetSelectedItem() && Inventory->GetSelectedItem()->Name == TEXT("신호탄")) Type = EEscapeType::FlareGun;
	
	if (Type == EEscapeType::None) Type = EscapeCheckRayCast();

	switch (Type) {
	case EEscapeType::None:
		UE_LOG(LogTemp, Warning, TEXT("None"));
		break;
	case EEscapeType::Ship:
		UE_LOG(LogTemp, Warning, TEXT("Ship"));
		break;
	case EEscapeType::HotAirBalloon:
		UE_LOG(LogTemp, Warning, TEXT("HotAirBalloon"));
		break;
	case EEscapeType::FlareGun:
		UE_LOG(LogTemp, Warning, TEXT("FlareGun"));
		UManagers::Get(GetWorld())->Sound()->PlaySingleSound(GetWorld(), ESound::S_SignalFlare);
		break;
	}
}

void ACPP_Player::ItemCheckRayCast()
{
	FHitResult Hit;

	FVector Forward = GetForwardVector();
	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = Start + Forward * ItemCheckRayLength;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, CQP)) {
		auto Item = Cast<AItem>(Hit.GetActor());
		if (Item) Item->Focused();
		if (FocusedItem && FocusedItem != Item) FocusedItem->NotFocused();
		FocusedItem = Item;
	}
	else if (FocusedItem) {
		FocusedItem->NotFocused();
		FocusedItem = nullptr;
	}
}

void ACPP_Player::ConstructCheckRayCast()
{
	FHitResult WaterHit;
	FHitResult ObjectHit;

	bool Water;
	bool Object;

	FVector Forward = GetForwardVector();
	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = Start + Forward * ConstructCheckRayLength;

	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.5f, 0, 1);

	Water = GetWorld()->LineTraceSingleByChannel(WaterHit, Start, End, ECC_GameTraceChannel3, CQP);
	Object = GetWorld()->LineTraceSingleByChannel(ObjectHit, Start, End, ECC_Visibility, CQP);

	if (Water && Object) {
		float Water_Z = WaterHit.Location.Z;
		float Object_Z = ObjectHit.Location.Z;

		if (Water_Z > Object_Z) ConstructCheckRayCastAction(WaterHit);
		else ConstructCheckRayCastAction(ObjectHit);
	}
	else if (Water) ConstructCheckRayCastAction(WaterHit);
	else if (Object) ConstructCheckRayCastAction(ObjectHit);
	else IsConstruct = false;
}

void ACPP_Player::DrinkCheckRayCast()
{
	FHitResult Hit;

	FVector Forward = GetForwardVector();
	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = Start + Forward * DrinkCheckRayLength;

	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.5f, 0, 1);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel3, CQP)) {
		if (Hit.GetActor()->FindComponentByClass<UWaterBodyLakeComponent>()) IsDrinkable = true;
		else IsDrinkable = false;
	}
	else IsDrinkable = false;
}

void ACPP_Player::MultipleItemCheckRayCast()
{
	FHitResult Hit;

	FVector Forward = GetForwardVector();
	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = Start + Forward * ItemCheckRayLength;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, CQP)) {
		auto MultipleItem = Cast<AMultipleItem>(Hit.GetActor());
		if (MultipleItem) MultipleItem->Focused();
		if (FocusedMultipleItem && FocusedMultipleItem != MultipleItem) FocusedMultipleItem->NotFocused();
		FocusedMultipleItem = MultipleItem;
	}
	else if (FocusedMultipleItem) {
		FocusedMultipleItem->NotFocused();
		FocusedMultipleItem = nullptr;
	}
}

EEscapeType ACPP_Player::EscapeCheckRayCast()
{
	FHitResult Hit;

	FVector Forward = GetForwardVector();
	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = Start + Forward * ItemCheckRayLength;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, CQP)) {
		auto Item = Cast<AItem>(Hit.GetActor());
		if (Item && Item->Constructed) {
			if (Item->ActorHasTag("BP_Ship")) return EEscapeType::Ship;
			else if (Item->ActorHasTag("BP_HotAirBalloon")) return EEscapeType::HotAirBalloon;
		}
	}
	return EEscapeType::None;
}

void ACPP_Player::Shake()
{
	if (auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
		PlayerController->ClientStartCameraShake(CameraShake);
		UManagers::Get(GetWorld())->Sound()->PlaySingleSound(GetWorld(), ESound::S_Earthquake);
	}
}

FVector ACPP_Player::GetForwardVector()
{
	return PlayerCamera->GetForwardVector();
}

TObjectPtr<UTexture2D> ACPP_Player::GetSelectedItemBG()
{
	return SelectedItemBGTexture;
}

TObjectPtr<UTexture2D> ACPP_Player::GetNotSelectedItemBG()
{
	return NotSelectedItemBGTexture;
}

void ACPP_Player::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->ActorHasTag("Landscape") || OtherActor->FindComponentByClass<UWaterBodyLakeComponent>() || OtherActor->FindComponentByClass<UWaterBodyOceanComponent>()) {
		if (IsJumpStart || IsJumping) {
			IsJumpEnd = true;
			IsJumping = false;
			IsJumpStart = false;
		}
	}
}

void ACPP_Player::ConstructCheckRayCastAction(FHitResult& Hit)
{
	auto Actor = Hit.GetActor();
	auto ConstructPoint = Cast<AItem>(Actor);
	if (ConstructPoint && ConstructPoint->IsConstructPoint) CQP.AddIgnoredActor(ConstructPoint);
	else if (Actor) {
		if (Actor->ActorHasTag("Landscape")) IsConstruct = Inventory->ShowConstructPoint("Landscape", Hit.Location);
		else if (Actor->FindComponentByClass<UWaterBodyOceanComponent>()) IsConstruct = Inventory->ShowConstructPoint("WaterBodyOcean", Hit.Location);
		else if (Actor->ActorHasTag("HotAirBalloonLandingSite")) IsConstruct = Inventory->ShowConstructPoint("BP_HotAirBalloonLandingSite", Hit.Location);
	}
}
