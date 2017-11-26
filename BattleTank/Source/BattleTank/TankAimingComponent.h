// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

// Enum for tank aiming state
UENUM(BlueprintType)
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Empty,
	Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void Fire();

	EFiringStatus GetFiringStatus() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UPROPERTY(BlueprintReadOnly, Category = "Firing")
	int32 CurrentAmmo = 3;

private:

	void MoveBarrelTowards(FVector AimDirection);
	void RotateTurretTowards(FVector AimDirection);
	bool IsBarrelMoving();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 5000.0;	// TODO find sensible default

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float AimingLockedTolerance = 0.05f;

	double LastFireTime;
	FVector AimDirection;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
};
