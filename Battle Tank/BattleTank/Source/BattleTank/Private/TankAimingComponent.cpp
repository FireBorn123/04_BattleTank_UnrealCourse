// Copyright Trevor Randall

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;  
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	//Following line not necessary
	//LastTimeFired = FPlatformTime::Seconds();
}

void UTankAimingComponent::AimingInitalize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
};

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastTimeFired) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
	// TODO Handle aiming and locked states
};

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.1);
};

void UTankAimingComponent::AimAt(FVector OutHitLocation)
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	// If no solution found, do nothing


}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure (Barrel || Turret)) { return; }

	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Turret->RotateTurret(DeltaRotator.Yaw); //1 equals 100% of its max speed //Also works as Barrel and turret point in the same direction
	Barrel->Elevate(DeltaRotator.Pitch); //1 equals 100% of its max speed
}

void UTankAimingComponent::FireProjectile()
{
	if (FiringState != EFiringState::Reloading)
	{
		//Spawn a projectile at the socket location
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("ProjectileFirePoint")),
			Barrel->GetSocketRotation(FName("ProjectileFirePoint")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastTimeFired = FPlatformTime::Seconds();
	}
}

