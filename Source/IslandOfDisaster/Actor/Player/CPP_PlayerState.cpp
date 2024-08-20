// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_PlayerState.h"
#include "../../Manager/Managers.h"
#include "../../Manager/UIManager.h"
#include "../../UI/PlayerInfoUI.h"
#include <random>
#include "../../Manager/DisasterManager.h"
#include "../Disaster/Disaster.h"
#include "CPP_Player.h"
#include "../Item/Spawner.h"
#include "EngineUtils.h"
#include "../TimeOfDay.h"

#define Max(a, b) a > b ? a : b
#define Min(a, b) a < b ? a : b
#define Increase(Type, Value) Cur##Type = Min(Cur##Type + Value, Max##Type);
#define Decrease(Type, Value) Cur##Type = Max(Cur##Type - Value, 0);

void ACPP_PlayerState::BeginPlay() {
	Super::BeginPlay();

	Initialize();
}

void ACPP_PlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isOnTimer) {
		Timer += DeltaTime;
		UManagers::Get(GetWorld())->TimeOfDay()->TimeToSunRotation(Hours, Timer / RealTimeSecondToInGameHour * 60);
		if (Timer >= RealTimeSecondToInGameHour) {
			Hours++;
			PhysiologicalPhenomenonUnit++;
			TemperatureAndHumidityUnit++;
			Timer = 0;

			Disaster->Effect1();
			Disaster->Effect2();
			Disaster->Effect3();

			if (PhysiologicalPhenomenonUnit == 2) {
				DecreaseHunger(5);
				DecreaseThirsty(5);

				PhysiologicalPhenomenonUnit = 0;
			}

			if (TemperatureAndHumidityUnit == 4) {
				ChangeTemperature();
				ChangeHumidity();
				if (Hours <= 7 || Hours >= 20) DecreaseTemperature(Random(7, 10));

				TemperatureAndHumidityUnit = 0;
			}

			if (Hours == 24) {
				Days++;
				Hours = 0;

				for (auto Spawner : Spawners) {
					if (Random(0, 1)) Spawner->Spawn();
				}
			}
		}

		StateApplyToUI();
	}
}

void ACPP_PlayerState::Initialize()
{
	isOnTimer = false;
	Timer = 0;

	Days = 1;
	Hours = 9;

	AdditionalTemperature = 0;
	AdditionalHumidity = 0;

	ChangeTemperature();
	ChangeHumidity();

	StateApplyToUI();

	StartTimer();

	//UManagers::Get(GetWorld())->Disaster()->SetDisaster(EDisasterType(Random(0, 4)));
	UManagers::Get(GetWorld())->Disaster()->SetDisaster(EDisasterType(2));
	
	Disaster = UManagers::Get(GetWorld())->Disaster()->Disaster;

	UWorld* World = GetWorld();
	for (TActorIterator<ASpawner> It(World); It; ++It) {
		Spawners.Add(*It);
		if (Random(0, 1)) It->Spawn();
	}
}

int ACPP_PlayerState::Random(int MinInclusive, int MaxInclusive)
{
	std::random_device random;
	std::mt19937 engine(random()); 
	std::uniform_int_distribution<int> distribution(MinInclusive, MaxInclusive);  
	return distribution(engine);
}

void ACPP_PlayerState::StartTimer()
{
	isOnTimer = true;
}

void ACPP_PlayerState::StateApplyToUI()
{
	auto PlayerInfoWidget = Cast<UPlayerInfoUI>(UManagers::Get(GetWorld())->UI()->GetWidget(EWidgetType::PlayerInfo));
	PlayerInfoWidget->SetHP(MaxHP, CurHP);
	PlayerInfoWidget->SetHunger(MaxHunger, CurHunger);
	PlayerInfoWidget->SetThirsty(MaxThirsty, CurThirsty);
	PlayerInfoWidget->SetTemperature(MaxTemperature, CurTemperature);
	PlayerInfoWidget->SetHumidity(MaxHumidity, CurHumidity);
	PlayerInfoWidget->SetDays(Days);
	PlayerInfoWidget->SetHours(Hours, Timer / RealTimeSecondToInGameHour * 60);
}

void ACPP_PlayerState::IncreaseHP(float Value)
{
	Increase(HP, Value);
}

void ACPP_PlayerState::IncreaseHunger(float Value)
{
	Increase(Hunger, Value);
}

void ACPP_PlayerState::IncreaseThirsty(float Value)
{
	Increase(Thirsty, Value);
}

void ACPP_PlayerState::IncreaseTemperature(float Value)
{
	Increase(Temperature, Value);
}

void ACPP_PlayerState::IncreaseHumidity(float Value)
{
	Increase(Humidity, Value);
}

void ACPP_PlayerState::DecreaseHP(float Value)
{
	Decrease(HP, Value);
}

void ACPP_PlayerState::DecreaseHunger(float Value)
{
	if (CurHunger > 0) {
		Decrease(Hunger, Value);
	}
	else Decrease(HP, Value / 2);
}

void ACPP_PlayerState::DecreaseThirsty(float Value)
{
	if (CurThirsty > 0) {
		Decrease(Thirsty, Value);
	}
	else Decrease(HP, Value / 2);
}

void ACPP_PlayerState::DecreaseTemperature(float Value)
{
	Decrease(Temperature, Value);
}

void ACPP_PlayerState::DecreaseHumidity(float Value)
{
	Decrease(Humidity, Value);
}

void ACPP_PlayerState::ChangeTemperature()
{
	CurTemperature = 22 + Random(0, 5) + AdditionalTemperature;
}

void ACPP_PlayerState::ChangeHumidity()
{
	CurHumidity = 65 + Random(0, 7) + AdditionalHumidity;
}

void ACPP_PlayerState::ChangeAdditionalTemperature()
{
	AdditionalTemperature += Random(2, 3);
}

void ACPP_PlayerState::ChangeAdditionalHumidity()
{
	AdditionalHumidity += Random(2, 4);
}
