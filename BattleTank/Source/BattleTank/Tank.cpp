// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "UObjectGlobals.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: Tank %s Constructed in C++"), *TankName);
	// Dont need to protect constructor as added at construction
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY: Tank %s BeginPlay in C++"), *TankName);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded) 
	{
		//Spawn a projectile at the socket location on barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}