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

	if (!ensure(PlayerTank)) { return; }
	if (!ensure(Cast<ATank>(GetPawn()))) { return; }
	
	MoveToActor(PlayerTank, AcceptanceRadius);

	Cast<ATank>(GetPawn())->AimAt(PlayerTank->GetActorLocation());
	Cast<ATank>(GetPawn())->Fire();
	
	// TODO fire if ready
}