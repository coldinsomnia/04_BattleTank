// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack || RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	//UE_LOG(LogTemp, Warning, TEXT("ITM:  Setting left Throttle: %f"), Throw);
	RightTrack->SetThrottle(Throw);
	//UE_LOG(LogTemp, Warning, TEXT("ITM:  Setting right Throttle: %f"), Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack || RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	//UE_LOG(LogTemp, Warning, TEXT("ITR:  Setting left Throttle: %f"), Throw);
	RightTrack->SetThrottle(-Throw);
	//UE_LOG(LogTemp, Warning, TEXT("ITR:  Setting right Throttle: %f"), -Throw);

}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet || RightTrackToSet)) { return; }

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
	IntendTurnRight(AIRightThrow);
}