// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void Fire();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Setup")
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();
	
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 5000.0;	// TODO find sensible default

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	UTankBarrel* Barrel = nullptr;	// TODO remove

	double LastFireTime;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

};
