// Copyright Trevor Randall

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
// Depends on movement component via pathfinding system


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

//Call Every Frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AIControlledTank = GetPawn();

	if (!ensure(PlayerTank && AIControlledTank)) { return; }
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius, true, true, false); 
	
	//Aim Towards Player Tank
	auto AimingComponent = AIControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }

	AimingComponent->AimAt (PlayerTank->GetActorLocation());

	// Fire Projectile
	// TODO Fix firing
	// AIControlledTank->FireProjectile();
}
