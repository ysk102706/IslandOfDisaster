// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "../../Manager/Managers.h"
#include "../../Manager/DataLoadManager.h"
#include "../Player/CPP_Player.h"
#include "Spawner.h"
#include "Inventory.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	Mesh = FindComponentByClass<UStaticMeshComponent>();

	IsLoaded = false;

	NotFocused();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::Init(UTexture2D* ItemTexture, FString ItemName, FString ItemDescription, int ManufactureCount, bool IsItemConstruct, bool IsItemUsable, int ItemDurability, bool IsItemExit)
{
	Texture = ItemTexture;
	Name = ItemName;
	Description = ItemDescription;
	ManufacturedItemCount = ManufactureCount;
	IsConstruct = IsItemConstruct;
	IsUsable = IsItemUsable;
	Durability = ItemDurability;
	IsExit = IsItemExit;

	IsLoaded = true;
}

void AItem::Focused()
{
	if (!IsFocused && !IsConstructPoint && !Constructed) {
		IsFocused = true;
		IsNotFocused = false;

		int MatCnt = 0;
		Mesh->bRenderCustomDepth = true;
		for (int i = 0; i < Mesh->GetNumMaterials(); i++) Mesh->SetMaterial(i, FocusedMaterials[MatCnt++]);

		if (Mesh->GetNumChildrenComponents()) {
			auto SM = Cast<UStaticMeshComponent>(Mesh->GetChildComponent(0));
			if (SM) {
				SM->bRenderCustomDepth = true;
				for (int i = 0; i < SM->GetNumMaterials(); i++) SM->SetMaterial(i, FocusedMaterials[MatCnt++]);
			}
		}
	}
}

void AItem::NotFocused()
{
	if (!IsNotFocused) {
		IsNotFocused = true;
		IsFocused = false;

		int MatCnt = 0;
		Mesh->bRenderCustomDepth = false;
		for (int i = 0; i < Mesh->GetNumMaterials(); i++) Mesh->SetMaterial(i, DefaultMaterials[MatCnt++]);

		if (Mesh->GetNumChildrenComponents()) {
			auto SM = Cast<UStaticMeshComponent>(Mesh->GetChildComponent(0));
			if (SM) {
				SM->bRenderCustomDepth = false;
				for (int i = 0; i < SM->GetNumMaterials(); i++) SM->SetMaterial(i, DefaultMaterials[MatCnt++]);
			}
		}
	}
}

bool AItem::Picked()
{
	if (!IsLoaded) UManagers::Get(GetWorld())->DataLoad()->LoadItems(Id, this);
	if (Constructed) return false;
	if (UManagers::Get(GetWorld())->Player()->Inventory->AddItem(this)) {
		SetPhysics(false);
		SetActorLocation(FVector(0, 0, -100));
		Mesh->SetWorldLocation(FVector(0, 0, -100));

		if (Spawner) {
			Spawner->IsSpawned = false;
			Spawner->SpawnedActor = nullptr;
		}

		return true;
	}
	return false;
}

void AItem::Droped()
{
	if (!IsLoaded) UManagers::Get(GetWorld())->DataLoad()->LoadItems(Id, this);
	auto Player = UManagers::Get(GetWorld())->Player();
	FVector Pos = Player->GetActorLocation() + FVector(0, 0, 80);
	SetPhysics(true);
	SetActorLocation(Pos);
	Mesh->SetWorldLocation(Pos);
	Mesh->AddVelocityChangeImpulseAtLocation(UManagers::Get(GetWorld())->Player()->GetForwardVector() * 500, Pos);
}

void AItem::Construct(FVector Pos)
{
	SetPhysics(false);
	SetActorLocation(Pos);
	SetWorldLocation(Pos);

	Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	Mesh->SetWorldRotation(FRotator(0, 0, 0));

	if (Mesh->GetNumChildrenComponents()) {
		auto SM = Cast<UStaticMeshComponent>(Mesh->GetChildComponent(0));
		if (SM) SM->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	}

	Constructed = true;
}

void AItem::ConstructPoint(bool Value)
{
	for (int i = 0; i < Mesh->GetNumMaterials(); i++) Mesh->SetMaterial(i, Value ? ConstructAvailableMaterial : ConstructUnavailableMaterial);

	if (Mesh->GetNumChildrenComponents()) {
		auto SM = Cast<UStaticMeshComponent>(Mesh->GetChildComponent(0));
		if (SM) for (int i = 0; i < SM->GetNumMaterials(); i++) SM->SetMaterial(i, Value ? ConstructAvailableMaterial : ConstructUnavailableMaterial);
	}
}

void AItem::DestroyActor()
{
	RemoveFromRoot();
	Destroy();
}

void AItem::SetPhysics(bool Value)
{
	Mesh->SetSimulatePhysics(Value);
}

void AItem::SetWorldLocation(FVector Pos)
{
	Mesh->SetWorldLocation(Pos);
}