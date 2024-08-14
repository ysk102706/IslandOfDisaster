// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MultipleItem.generated.h"

class ASpawner;

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
	class UMaterialInterface* DefaultMaterial;
	UPROPERTY(EditAnywhere, Category = Materials)
	class UMaterialInterface* FocusedMaterial;

	UPROPERTY(EditAnywhere, Category = Item)
	TArray<int> ItemList;

	TObjectPtr<ASpawner> Spawner;

private:
	TObjectPtr<UStaticMeshComponent> Mesh;

	bool IsFocused;
	bool IsNotFocused;

};
