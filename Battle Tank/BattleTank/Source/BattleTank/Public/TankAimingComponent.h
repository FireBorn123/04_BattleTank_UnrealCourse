// Copyright Trevor Randall

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward Declaration
class UTankBarrel; 
class UTankTurret;


// Hold barrel's properties
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AimAt(FVector OutHitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void AimingInitalize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:
	//Determine Firing State
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0;


	void MoveBarrelTowards(FVector AimDirection);



};
