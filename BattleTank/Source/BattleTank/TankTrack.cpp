// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	if (!TankRoot)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to cast root component to TankRoot!"));
		return;
	}
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}