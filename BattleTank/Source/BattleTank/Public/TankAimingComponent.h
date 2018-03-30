// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Pawn.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Ready
};

// Holds properties for barrel
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, category = "State")
	EFiringStatus FiringState = EFiringStatus::Ready;


	UPROPERTY(EditDefaultsOnly, Category = "Gun Setup")
	float LaunchSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun Setup")
	float FireCooldown = 3.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gun Setup")
	float LastShotTime = -3.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gun Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitializeAiming(UTankBarrel* SetBarrel, UTankTurret* SetTurret);


	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void Fire();


private:
	UTankBarrel * Barrel = nullptr;

	UTankTurret * Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	void MoveTurretTowards(FVector TurretAimDirection);
};

