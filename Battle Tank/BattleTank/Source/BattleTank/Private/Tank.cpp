// Fill out your copyright notice in the Description page of Project Settings.

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

	// No need to protect pointers as added at construction
	
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	
	// Addition of movement component to Tank, added at construction
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{		
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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