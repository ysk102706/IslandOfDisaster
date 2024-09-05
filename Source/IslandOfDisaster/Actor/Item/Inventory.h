// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Inventory.generated.h"

UCLASS()
class ISLANDOFDISASTER_API AInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	AInventory();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	TObjectPtr<AItem> GetItem(int Idx);
	bool AddItem(TObjectPtr<AItem> Item);
	void DropItem();
	void SelectItem(int Idx);
	void ConstructItem();

	void SetWorld(UWorld* PlayerWorld);
	void SetNoneItemTexture(UTexture2D* Texture);
	void SetInventoryUI(int Idx, TArray<TObjectPtr<AItem>>& Items);

	bool ShowConstructPoint(FString HitObjectName, FVector HitPos);

	int GetItemCount(FString Name);
	void Consume(FString Name, int Count);

	TObjectPtr<AItem> GetSelectedItem();

	int GetSelectedItemIdx();

private:
	UPROPERTY()
	UWorld* World;

	TArray<TObjectPtr<AItem>> Contents[7];
	TObjectPtr<TMap<FString, int>> ContentMap;
	int SelectedItemIdx;

	UPROPERTY()
	TObjectPtr<UTexture2D> NoneItemTexture;

	UPROPERTY()
	AItem* ConstructPointObject;
	bool IsConstruct;

};
