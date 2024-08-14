// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"

void AAsteroid::Effect1()
{
	Super::Effect1();
	
	if (IsChangeDay) 1;
}

void AAsteroid::Effect2()
{
	int Hour = (Hours + 9) % 24;
	if (Hour >= 21 && Hour <= 6) 1;
}

void AAsteroid::Effect3()
{
	int Hour = (Hours + 9) % 24;
	if (Hour >= 21 && Hour <= 6 && !IsLight) {
		1;
		
	}

	IsChangeDay = false;
	IsLight = false;
}