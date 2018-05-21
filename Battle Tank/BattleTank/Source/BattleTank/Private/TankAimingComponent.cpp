// Copyright Trevor Randall

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;  

	// ...
}

void UTankAimingComponent::AimingInitalize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
};

void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileFirePoint"));

	//Calculate the outlaunch Velocity
	TArray<AActor*> ActorIgnoreList;
	ActorIgnoreList.Add(GetOwner());
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		OutHitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace, // Parameter must be present to report bug
		FCollisionResponseParams::DefaultResponseParam,
		ActorIgnoreList,
		false
	);

	
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution Found"), Time);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), Time);
	}
	// If no solution found, do nothing


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure (Barrel || !Turret)) { return; }

	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Turret->RotateTurret(DeltaRotator.Yaw); //1 equals 100% of its max speed //Also works as Barrel and turret point in the same direction
	Barrel->Elevate(DeltaRotator.Pitch); //1 equals 100% of its max speed
}
