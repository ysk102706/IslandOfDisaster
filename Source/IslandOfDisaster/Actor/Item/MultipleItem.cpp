// Fill out your copyright notice in the Description page of Project Settings.


#include "MultipleItem.h"
#include "Spawner.h"
#include "../../Manager/Managers.h"
#include "../Player/CPP_Player.h"
#include "../Player/CPP_PlayerState.h"
#include "../Item/Inventory.h"
#include "../../Manager/DataLoadManager.h"

AMultipleItem::AMultipleItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMultipleItem::BeginPlay()
{
	Super::BeginPlay();

	Mesh = FindComponentByClass<UMeshComponent>();

	if (MeshType) Mesh = Cast<USkeletalMeshComponent>(Mesh);
	else Mesh = Cast<UStaticMeshComponent>(Mesh);

	NotFocused();
}

void AMultipleItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMultipleItem::Focused()
{
	if (!IsFocused) {
		IsFocused = true;
		IsNotFocused = false;

		Mesh->bRenderCustomDepth = true;
		for (int i = 0; i < Mesh->GetNumMaterials(); i++) Mesh->SetMaterial(i, FocusedMaterials[i]);
	}
}

void AMultipleItem::NotFocused()
{
	if (!IsNotFocused) {
		IsNotFocused = true;
		IsFocused = false;

		Mesh->bRenderCustomDepth = false;
		for (int i = 0; i < Mesh->GetNumMaterials(); i++) Mesh->SetMaterial(i, DefaultMaterials[i]);
	}
}

void AMultipleItem::Picked()
{
	for (auto Id : ItemList) {
		TObjectPtr<AItem> Item = UManagers::Get(GetWorld())->DataLoad()->SpawnItemActor(GetWorld(), Id);

		UManagers::Get(GetWorld())->DataLoad()->LoadItems(Id, Item);

		if (UManagers::Get(GetWorld())->Player()->Inventory->AddItem(Item)) {
			Item->SetActorLocation(FVector(0, 0, -100));
			Item->SetWorldLocation(FVector(0, 0, -100));
		}
		else Item->Droped();
	}

	Spawner->IsSpawned = false;
	Spawner->SpawnedActor = nullptr;
	UManagers::Get(GetWorld())->Player()->GetController()->GetPlayerState<ACPP_PlayerState>()->SpawnCnt--;

	DestroyActor();
}

void AMultipleItem::DestroyActor()
{
	RemoveFromRoot();
	Destroy();
}