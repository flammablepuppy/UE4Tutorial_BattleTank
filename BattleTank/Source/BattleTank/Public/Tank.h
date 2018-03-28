// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

// Forward declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Gun Setup")
	float LaunchSpeed = 4000.f;

protected:
	UTankAimingComponent * TankAimingComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Gun Setup")
	float FireCooldown = 3.f;
	float LastShotTime = -3.f;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
	UTankMovementComponent* TankMoveComp;

private:	
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Gun Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Local reference for spawning projectiles.
	UTankBarrel* BarrelRef = nullptr;

};
