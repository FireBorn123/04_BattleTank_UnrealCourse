// Copyright Trevor Randall

#include "Tank.h"
#include "GameFramework/Actor.h"
#include "BattleTank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); //Needed for BP BeginPlay to run
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank has been destroyed"));
	};
	
	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/ (float)TankStartHealth;
}