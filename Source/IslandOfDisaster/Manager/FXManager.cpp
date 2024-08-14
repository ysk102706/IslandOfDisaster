// Fill out your copyright notice in the Description page of Project Settings.


#include "FXManager.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraActor.h"
#include "Managers.h"
#include "../Actor/Player/CPP_Player.h"

void UFXManager::Tick(const UWorld* World)
{
	if (NSC_Rain) NSC_Rain->SetWorldLocation(UManagers::Get(GetWorld())->Player()->GetActorLocation());
	if (NSC_Wind) NSC_Wind->SetWorldLocation(UManagers::Get(GetWorld())->Player()->GetActorLocation());
}

TObjectPtr<UNiagaraSystem> UFXManager::GetFX(EFXType Type)
{
	TObjectPtr<UNiagaraSystem> FX = nullptr;

	switch (Type) {
	case EFXType::FX_Asteroid:
		FX = NS_Asteroid;
		break;
	case EFXType::Gas:
		FX = NS_Gas;
		break;
	case EFXType::Rain:
		FX = NS_Rain;
		break;
	case EFXType::ShootingStar:
		FX = NS_ShootingStar;
		break;
	case EFXType::Star:
		FX = NS_Star;
		break;
	case EFXType::Wind:
		FX = NS_Wind;
		break;
	}

	return FX;
}

void UFXManager::SetComponent(EFXType Type, TObjectPtr<UNiagaraComponent> Component)
{
	switch (Type) {
	case EFXType::Rain:
		NSC_Rain = Component;
		break;
	case EFXType::ShootingStar:
		NSC_ShootingStar = Component;
		break;
	case EFXType::Star:
		NSC_Star = Component;
		break;
	case EFXType::Wind:
		NSC_Wind = Component;
		break;
	}
}

TObjectPtr<UNiagaraComponent> UFXManager::GetComponent(EFXType Type)
{
	TObjectPtr<UNiagaraComponent> NSC = nullptr;

	switch (Type) {
	case EFXType::Rain:
		NSC = NSC_Rain;
		break;
	case EFXType::ShootingStar:
		NSC = NSC_ShootingStar;
		break;
	case EFXType::Star:
		NSC = NSC_Star;
		break;
	case EFXType::Wind:
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

void UFXManager::SetActiveFX(EFXType Type, bool Value)
{
	TObjectPtr<UNiagaraComponent> NSC = GetComponent(Type);

	if (NSC) NSC->SetVisibility(Value);
}
