// Copyright Trevor Randall (Commit Check)

#include "TankPlayerController_Cpp.h"
#include "GameFramework/Pawn.h"
#include "Public/CollisionQueryParams.h"
#include "Engine/World.h"

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankPlayerController_Cpp::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

	
void ATankPlayerController_Cpp::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
    AimTowardsCrosshairs();
}

void ATankPlayerController_Cpp::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PosessedTank = Cast<ATank>(InPawn); //Broadcasting Instance
		if (!ensure(PosessedTank)) { return; }

		// Suscribe our local method to the Tank's death event
		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController_Cpp::OnPosessedTankDeath);
		
	}
}

void ATankPlayerController_Cpp::OnPosessedTankDeath()
{
	StartSpectatingOnly();
	UE_LOG(LogTemp, Warning, TEXT("Player Tank Destroyed"))
}

void ATankPlayerController_Cpp::AimTowardsCrosshairs()
{
	if (!GetPawn()) { return; } //ex. if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector OutHitLocation; // Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(OutHitLocation);
	if (bGotHitLocation) //Has "side-effect", is going to raytrace
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
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return false;
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
		ECollisionChannel::ECC_Camera, 
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



