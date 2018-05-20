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
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s 2700_TankConstructor"), *TankName)
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //Needed for BP BeginPlay to run
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s 2700_TankBeginPlay"), *TankName)
}

void ATank::AimAt(FVector OutHitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(OutHitLocation, LaunchSpeed);
}

void ATank::FireProjectile()
{
	if (!ensure(Barrel)) { return; }
	bool isReloaded = (FPlatformTime::Seconds() - LastTimeFired) > ReloadTimeInSeconds;
	if (isReloaded)
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