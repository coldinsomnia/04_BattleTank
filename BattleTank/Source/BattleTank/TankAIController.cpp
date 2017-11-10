// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No player tank found!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank found: %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("No player tank found by AI Controller"));
		return; 
	}

	auto ThisTank = GetControlledTank();
	if (!ThisTank) 
	{ 
		UE_LOG(LogTemp, Error, TEXT("No controlled tank found by AI controller"));
		return; 
	}
	
	// TODO move towards player

	ThisTank->AimAt(PlayerTank->GetActorLocation());
	
	// TODO fire if ready
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	else return Cast<ATank>(PlayerPawn);
}