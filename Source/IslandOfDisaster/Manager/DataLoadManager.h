// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SQLiteDatabase.h"
#include "DataLoadManager.generated.h"

class AItem;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ISLANDOFDISASTER_API UDataLoadManager : public UObject
{
	GENERATED_BODY()
	
public:
	void LoadManufacturedItemList(const UWorld* World);
	void LoadSelectedManufacturedItem(const UWorld* World, int Id);
	void LoadIngredientItems(const UWorld* World, int Id);
	TObjectPtr<AItem> SpawnItemActor(UWorld* World, int Id);
	void LoadItems(int Id, AItem* Item);

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<UTexture2D>> Textures;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> Items;

private:
	FSQLiteDatabase* Database;
	FSQLitePreparedStatement* PStmt;

};
