// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankMovementComponent.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

//Call Every Frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AIControlledTank = Cast<ATank>(GetPawn());
	{
		AIControlledTank->AimAt(PlayerTank->GetActorLocation());
	}


	if (!PlayerTank) { return; } else
	{	
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, false); 
	
		//Aim Towards Player Tank
		AIControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire Projectile
		AIControlledTank->FireProjectile(); //TODO don't fire every frame
	}
}
