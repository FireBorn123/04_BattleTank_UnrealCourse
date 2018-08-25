// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"
#include "Engine/World.h"
#include "BattleTank.h"
#include "SpawnPoint.h"
#include "SprungWheel.h"

UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTracks::BeginPlay()
{
	Super::BeginPlay();

}

void UTankTracks::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle*TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* TankWheel : Wheels)
	{
		TankWheel->AddDrivingForce(ForcePerWheel);
	}
}

void UTankTracks::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp <float> (Throttle, -2, 2);
	DriveTrack(CurrentThrottle);
}

TArray<ASprungWheel*> UTankTracks::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) { continue; }

		AActor* SpawnedChild = SpawnPointChild->GetAttachedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
	}

	return ResultArray;
}