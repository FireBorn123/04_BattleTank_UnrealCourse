// Copyright Trevor Randall

#include "TankAIController.h"
#include "Engine/World.h"
#include "BattleTank.h"
#include "Tank.h" //So we can implement on death
#include "TankAimingComponent.h"


// Depends on movement component via pathfinding system


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}



void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Suscribe our local method to the Tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
	}
}

void ATankAIController::OnPossesedTankDeath()
{
	if (GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp, Warning, TEXT("AI Tank Destroyed"))
};

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
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->FireProjectile(); // TODO Limit firing rate
	}
	
}

