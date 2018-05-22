// Copyright Trevor Randall

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController_Cpp.h"

void ATankPlayerController_Cpp::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

	
void ATankPlayerController_Cpp::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
    AimTowardsCrosshairs();
}

void ATankPlayerController_Cpp::AimTowardsCrosshairs()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector OutHitLocation; // Out parameter
	if (ensure(GetSightRayHitLocation(OutHitLocation))) //Has "side-effect", is going to raytrace
	{
		AimingComponent->AimAt(OutHitLocation);
	}
};


// Get world location of linetrace through crosshair, true if it hits landscape
bool ATankPlayerController_Cpp::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the Crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenPixelLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation); //Determines where the pixel is on the screen
	
	FVector LookDirection;
	if (ensure(GetLookDirection(ScreenPixelLocation, LookDirection)))
	{
		// Line trace along the LookDirection and see what you hit (to a maximum range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	
	return true;
}

//"De-project" the screen position of the crosshair to a world direction
bool ATankPlayerController_Cpp::GetLookDirection(FVector2D ScreenPixelLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenPixelLocation.X,
		ScreenPixelLocation.Y,
		CameraWorldLocation,
		LookDirection);
}

bool ATankPlayerController_Cpp::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if(GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation, 
		EndLocation, 
		ECollisionChannel::ECC_Visibility, 
		FCollisionQueryParams::DefaultQueryParam,
		FCollisionResponseParams::DefaultResponseParam))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false; //line trace didn't succeed
	;
}

