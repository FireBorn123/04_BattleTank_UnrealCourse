// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"
#include "BattleTank.h"



void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move the berrel the right amount arounf the frame, as dictated by the movement of the crosshair
	// Given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1., +1.); // Clamps relative speed, mutates relative speed
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ElevationClamped = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);
	

	SetRelativeRotation(FRotator(ElevationClamped, 0, 0));

}