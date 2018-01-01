// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::RotateTurret(float RelativeSpeed)
{
	// Get Turret to rotate relative to the tank 
	// Limit speed of rotation
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1., 1.);
	auto RotationChange = RelativeSpeed * MaxRotationDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRawRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRawRotation, 0));

	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: TankTurret is attached with a MaxRotationDegreesPerSecond of %f"), Time, RelativeSpeed)
}

