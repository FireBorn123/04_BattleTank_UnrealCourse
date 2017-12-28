// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player tank: %s"), *(PlayerTank->GetName()));
	}

}

//Call Every Frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsPlayer();
	// TODO Move towards the player
	// Fire if ready
}



ATank* ATankAIController::GetControlledAITank() const
{
	return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}
	return Cast<ATank>(PlayerPawn);
	
}

void ATankAIController::AimTowardsPlayer()
{
	if (!GetControlledAITank()) { return; }
	if (!GetPlayerTank()) { return; }
	FVector OutHitLocation;
	if (GetPlayerTank())
	{
		GetControlledAITank()->AimAt(GetPlayerTank()->GetActorLocation());
	}

}