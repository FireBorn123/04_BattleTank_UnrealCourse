// Copyright Trevor Randall

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::AimAt(FVector OutHitLocation)
{
	TankAimingComponent->AimAt(OutHitLocation, LaunchSpeed);
}

void ATank::FireProjectile()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastTimeFired) > ReloadTimeInSeconds;
	if (Barrel && isReloaded) 
	{
		//Spawn a projectile at the socket location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("ProjectileFirePoint")),
				Barrel->GetSocketRotation(FName("ProjectileFirePoint")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastTimeFired = FPlatformTime::Seconds();
	}



};