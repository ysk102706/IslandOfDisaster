// Fill out your copyright notice in the Description page of Project Settings.


#include "Disaster.h"
#include <random>

ADisaster::ADisaster()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADisaster::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADisaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ADisaster::Random(int MinInclusive, int MaxInclusive)
{
	std::random_device random;
	std::mt19937 engine(random());
	std::uniform_int_distribution<int> distribution(MinInclusive, MaxInclusive);
	return distribution(engine);
}

float ADisaster::Random(float MinInclusive, float MaxExclusive)
{
	std::random_device random;
	std::mt19937 engine(random());
	std::uniform_real_distribution<float> distribution(MinInclusive, MaxExclusive);
	return distribution(engine);
}

FVector ADisaster::RandomCircle(FVector Center, float MaxRange)
{
	float Distance = Random(0.01f, MaxRange);
	float Angle = Random(0.0f, 360.0f);

	return FVector(FMath::Cos(Angle), FMath::Sin(Angle), 0) * Distance + Center;
}
