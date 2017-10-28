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

void ATankPlayerController_Cpp::AimTowardsCrosshairs()
{
	if (!GetControlledTank()) { return; }

	// Get world location through linetrace
	// if it hiots the landscape
		//Tell controlled tank to aim at this point
};


ATank* ATankPlayerController_Cpp::GetControlledTank() const
{	
	return Cast<ATank>(GetPawn());
}


