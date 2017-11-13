// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("No player tank found by AI controller"));
		return;
	}

	if (!Cast<ATank>(GetPawn()))
	{ 
		UE_LOG(LogTemp, Error, TEXT("No controlled tank found by AI controller"));
		return; 
	}
	
	MoveToActor(PlayerTank, AcceptanceRadius);

	Cast<ATank>(GetPawn())->AimAt(PlayerTank->GetActorLocation());
	Cast<ATank>(GetPawn())->Fire();
	
	// TODO fire if ready
}