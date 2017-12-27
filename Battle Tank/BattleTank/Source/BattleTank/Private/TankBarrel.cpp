// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float DegreesPerSecond)
{
	// Move the berrel the right amount arounf the frame, as dictated by the movement of the crosshair
	// Given a max elevation speed, and the frame time
	UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate() called at speed %f"), DegreesPerSecond);

}

