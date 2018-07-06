// Copyright Trevor Randall

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController_Cpp.generated.h" 

// Forward declarations
class UTankAimingComponent;

/**
 * Responsible for helping player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController_Cpp : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef); //Because of macro, do not need to implement

private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.333333;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;
	
	// Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshairs();
	
	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	// FVector2D ScreenLocation();
	
	
};
