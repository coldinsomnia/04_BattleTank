// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	auto ClampedRotationSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);

	auto RotationChange = ClampedRotationSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.0f, RawNewRotation, 0.0f));
}