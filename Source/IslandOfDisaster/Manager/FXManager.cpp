// Fill out your copyright notice in the Description page of Project Settings.


#include "FXManager.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraActor.h"
#include "Managers.h"
#include "../Actor/Player/CPP_Player.h"

void UFXManager::Tick(const UWorld* World)
{
	if (NSC_Rain) NSC_Rain->SetWorldLocation(UManagers::Get(GetWorld())->Player()->GetActorLocation() + FVector(0, 0, 3000));
	if (NSC_Wind) NSC_Wind->SetWorldLocation(UManagers::Get(GetWorld())->Player()->GetActorLocation());
}

TObjectPtr<UNiagaraSystem> UFXManager::GetFX(EFXType Type)
{
	TObjectPtr<UNiagaraSystem> FX = nullptr;

	switch (Type) {
	case EFXType::FX_Asteroid:
		FX = NS_Asteroid;
		break;
	case EFXType::FX_Gas:
		FX = NS_Gas;
		break;
	case EFXType::FX_Rain:
		FX = NS_Rain;
		break;
	case EFXType::FX_ShootingStar:
		FX = NS_ShootingStar;
		break;
	case EFXType::FX_Star:
		FX = NS_Star;
		break;
	case EFXType::FX_Wind:
		FX = NS_Wind;
		break;
	}

	return FX;
}

void UFXManager::SetComponent(EFXType Type, TObjectPtr<UNiagaraComponent> Component)
{
	if (Component) Component->AddToRoot();
	
	switch (Type) {
	case EFXType::FX_Rain:
		NSC_Rain = Component;
		break;
	case EFXType::FX_ShootingStar:
		NSC_ShootingStar = Component;
		break;
	case EFXType::FX_Star:
		NSC_Star = Component;
		break;
	case EFXType::FX_Wind:
		NSC_Wind = Component;
		break;
	}
}

TObjectPtr<UNiagaraComponent> UFXManager::GetComponent(EFXType Type)
{
	TObjectPtr<UNiagaraComponent> NSC = nullptr;

	switch (Type) {
	case EFXType::FX_Rain:
		NSC = NSC_Rain;
		break;
	case EFXType::FX_ShootingStar:
		NSC = NSC_ShootingStar;
		break;
	case EFXType::FX_Star:
		NSC = NSC_Star;
		break;
	case EFXType::FX_Wind:
		NSC = NSC_Wind;
		break;
	}

	return NSC;
}

void UFXManager::SpawnFX(const UWorld* World, EFXType Type, FVector Pos)
{
	TObjectPtr<UNiagaraSystem> FX = GetFX(Type);

	if (FX) SetComponent(Type, UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, FX, Pos, FRotator(0, 0, 0))); 
}

void UFXManager::SetActiveFX(const UWorld* World, EFXType Type, bool Value)
{
	TObjectPtr<UNiagaraComponent> NSC = GetComponent(Type);

	if (!NSC) {
		SpawnFX(World, Type, FVector(0, 0, 0));
		NSC = GetComponent(Type);
	}

	NSC->SetVisibility(Value);
}
