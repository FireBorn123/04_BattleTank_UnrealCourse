// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController_Cpp.h"

void ATankPlayerController_Cpp::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
	}

}

	
void ATankPlayerController_Cpp::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
    AimTowardsCrosshairs();

	//  UE_LOG(LogTemp, Warning, TEXT("Player controller is ticking"));
}

ATank* ATankPlayerController_Cpp::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController_Cpp::AimTowardsCrosshairs()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) //Has "side-effect", is going to raytrace
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString());
			// Get world location through linetrace
			// if it hits the landscape
				//TODO Tell controlled tank to aim at this point
	}
};





// Get world location of linetrace through crosshair, true if it hits landscape
bool ATankPlayerController_Cpp::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	return true;
}