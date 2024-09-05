// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class ASpawner;

UCLASS()
class ISLANDOFDISASTER_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Init(UTexture2D* ItemTexture, FString ItemName, FString ItemDescription, int ManufactureCount, bool IsItemErection, bool IsItemUsable, int ItemDurability, bool IsItemExit);

	void Focused();
	void NotFocused();
	bool Picked();
	void Droped();
	void Construct(FVector Pos);
	void ConstructPoint(bool Value);

	void DestroyActor();

	void SetPhysics(bool Value);
	void SetWorldLocation(FVector Pos);

	UPROPERTY(EditAnywhere, Category = Materials)
	TArray<TObjectPtr<UMaterialInterface>> DefaultMaterials;
	UPROPERTY(EditAnywhere, Category = Materials)
	TArray<TObjectPtr<UMaterialInterface>> FocusedMaterials;
	UPROPERTY(EditAnywhere, Category = Materials)
	TObjectPtr<UMaterialInterface> ConstructAvailableMaterial;
	UPROPERTY(EditAnywhere, Category = Materials)
	TObjectPtr<UMaterialInterface> ConstructUnavailableMaterial;

	UPROPERTY(EditAnywhere)
	int Id;
	UPROPERTY(EditAnywhere)
	FString ConstructAvailablePlaceName;

	UPROPERTY()
	TObjectPtr<UTexture2D> Texture;

	UPROPERTY()
	TObjectPtr<ASpawner> Spawner;

	FString Name;
	FString Description;
	int ManufacturedItemCount;
	bool IsConstruct;
	bool IsUsable;
	int Durability;
	bool IsExit;

	bool Constructed;
	bool IsConstructPoint;

private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh;

	bool IsFocused;
	bool IsNotFocused;

	bool IsLoaded;

};