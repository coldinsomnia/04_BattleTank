// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack || RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//UE_LOG(LogTemp, Warning, TEXT("IntendMoveFoward: %f"), Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack || RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet || RightTrackToSet))
	{
		UE_LOG(LogTemp, Error, TEXT("Initialise failed in TankMovementComponent!"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Tracks set on AI tank"));
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super as we are replacing functionality

	auto TankForward = GetOwner()->GetActorForwardVector();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto AIForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	auto AIRightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	IntendMoveForward(AIForwardThrow);
	UE_LOG(LogTemp, Warning, TEXT("Forward throw to IntendMoveForward: %f"), AIForwardThrow);
	IntendTurnRight(AIRightThrow);
	UE_LOG(LogTemp, Warning, TEXT("Right throw to IntendTurnRight: %f"), AIRightThrow);
}