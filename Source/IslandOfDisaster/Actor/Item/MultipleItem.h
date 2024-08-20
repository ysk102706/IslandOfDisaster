// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MultipleItem.generated.h"

class ASpawner;

UENUM(BlueprintType)
enum EMeshType {
	StaticMesh		UMETA(DisplayName = "StaticMesh"),
	SkeletalMesh	UMETA(DisplayName = "SkeletalMesh")
};

UCLASS()
class ISLANDOFDISASTER_API AMultipleItem : public AActor
{
	GENERATED_BODY()

public:
	AMultipleItem();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void Focused();
	void NotFocused();
	void Picked();

	void DestroyActor();

	UPROPERTY(EditAnywhere, Category = Materials)
	TArray<TObjectPtr<UMaterialInterface>> DefaultMaterials;
	UPROPERTY(EditAnywhere, Category = Materials)
	TArray<TObjectPtr<UMaterialInterface>> FocusedMaterials;

	UPROPERTY(EditAnywhere, Category = Item)
	TArray<int> ItemList;

	UPROPERTY(EditAnywhere, Category = MeshType)
	int MeshType;

	TObjectPtr<ASpawner> Spawner;

private:
	TObjectPtr<UMeshComponent> Mesh;

	bool IsFocused;
	bool IsNotFocused;

};