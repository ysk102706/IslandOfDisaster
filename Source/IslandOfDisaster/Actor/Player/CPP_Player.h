// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CPP_Player.generated.h"

class AItem;
class AInventory;
class AMultipleItem;

UENUM(Blueprintable, BlueprintType)
enum EEscapeType {
	None			UMETA(DisplayName = "None"),
	Ship			UMETA(DisplayName = "Ship"),
	HotAirBalloon	UMETA(DisplayName = "HotAirBalloon"),
	FlareGun		UMETA(DisplayName = "FlareGun")
};

UCLASS()
class ISLANDOFDISASTER_API ACPP_Player : public ACharacter
{
	GENERATED_BODY()

public:
	ACPP_Player();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Camera(const FInputActionValue& Value);
	UFUNCTION()
	void PickItem(const FInputActionValue& Value);
	UFUNCTION()
	void DropItem(const FInputActionValue& Value);
	UFUNCTION()
	void SelectItem(const FInputActionValue& Value);
	UFUNCTION()
	void Manufacture(const FInputActionValue& Value);
	UFUNCTION()
	void Construct(const FInputActionValue& Value);
	UFUNCTION()
	void IF_Jump(const FInputActionValue& Value);
	UFUNCTION()
	void Drink(const FInputActionValue& Value);
	UFUNCTION()
	void Eat(const FInputActionValue& Value);
	UFUNCTION()
	void Escape(const FInputActionValue& Value);

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

	void ItemCheckRayCast();
	void ConstructCheckRayCast();
	void DrinkCheckRayCast();
	void MultipleItemCheckRayCast();
	EEscapeType EscapeCheckRayCast();

	void Shake();

	FVector GetForwardVector();

	TObjectPtr<UTexture2D> GetSelectedItemBG();
	TObjectPtr<UTexture2D> GetNotSelectedItemBG();

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IMC_Default;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Move;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Camera;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Pick;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Drop;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_SelectItem;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Manufacture;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Construct;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Jump;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Drink;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Eat;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Escape;

	UPROPERTY(EditAnywhere, Category=Ray)
	float ItemCheckRayLength;
	UPROPERTY(EditAnywhere, Category=Ray)
	float ConstructCheckRayLength;
	UPROPERTY(EditAnywhere, Category = Ray)
	float DrinkCheckRayLength;

	UPROPERTY(EditAnywhere, Category=Texture)
	TObjectPtr<UTexture2D> NoneItemTexture;
	UPROPERTY(EditAnywhere, Category=Texture)
	TObjectPtr<UTexture2D> SelectedItemBGTexture;
	UPROPERTY(EditAnywhere, Category=Texture)
	TObjectPtr<UTexture2D> NotSelectedItemBGTexture;

	UPROPERTY(EditAnywhere, Category=Minimap)
	TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY(EditAnywhere, Category=Minimap)
	TObjectPtr<class USceneCaptureComponent2D> CaptureComp;

	UPROPERTY(EditAnywhere, Category=Shake)
	TSubclassOf<class ULegacyCameraShake> CameraShake;

	UPROPERTY()
	TObjectPtr<AInventory> Inventory; 

	UPROPERTY(EditAnywhere, Category=GameMode)
	TSubclassOf<class AIslandOfDisasterGameModeBase> GameMode;

	bool IsJumpStart;
	bool IsJumping;
	bool IsJumpEnd;

	void StopSun();

private:
	void ConstructCheckRayCastAction(FHitResult& Hit);

	UPROPERTY()
	TObjectPtr<class UCameraComponent> PlayerCamera;

	UPROPERTY()
	TObjectPtr<AItem> FocusedItem;
	UPROPERTY()
	TObjectPtr<AMultipleItem> FocusedMultipleItem;

	bool IsOpenManufacture;
	float InputManufactureDelayTimer;

	FCollisionQueryParams CQP;

	bool IsConstruct;

	float JumpStartTimer;
	float JumpEndTimer;

	bool IsDrinkable;

	bool IsCutScenePlay;
	float CutSceneTimer;
	float CutSceneTime;
};