// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::InitializeMovement(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Track references must be set for the tank movement component in InitializeMoveComp function in the Tank Blueprint."))
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Track references must be set for the tank movement component in InitializeMoveComp function in the Tank Blueprint."))
		return;
	}
	LeftTrack->SetThrottle(Throw * 1.5);
	RightTrack->SetThrottle(-Throw * 1.5);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector MoveIntention = MoveVelocity.GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(TankForward, MoveIntention));

	IntendTurnRight(FVector::CrossProduct(TankForward, MoveIntention).Z);
}
