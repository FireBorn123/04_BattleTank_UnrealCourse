// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTracks.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we are replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention); 

	IntendMoveForward(ForwardThrow);

//	UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString);

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//TODO Prevent double speed due to dual control use
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
//	UE_LOG(LogTemp, Warning, TEXT("Intend to turn right: %f"), Throw);
	
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	//TODO Prevent double turn speed due to dual control use
}
