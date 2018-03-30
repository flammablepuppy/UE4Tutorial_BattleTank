// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{ 
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::InitializeAiming(UTankBarrel * SetBarrel, UTankTurret * SetTurret)
{
	Barrel = SetBarrel;
	Turret = SetTurret;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Called by Tank.cpp
void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!Barrel || !Turret) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("BarrelTip"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TurretAimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(TurretAimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Get current turret rotation, get barrel angle.
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator; 
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector TurretAimDirection)
{
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsTurretRotator = TurretAimDirection.Rotation();
	auto DeltaRotator = AimAsTurretRotator - TurretRotator;
	Turret->RotateTurret(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	// Protects a nullptr from crashing editor.
	if (!ProjectileBlueprint)
	{
		UE_LOG(LogTemp, Warning, TEXT("A projectile must be assigned in the Tank Blueprint"))
			return;
	}

	bool bCanFire = (GetWorld()->GetTimeSeconds() - LastShotTime) > FireCooldown;
	if (Barrel && bCanFire)
	{
		auto TankShell = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("BarrelTip")), Barrel->GetSocketRotation(FName("BarrelTip")));
		TankShell->LaunchProjectile(LaunchSpeed);
		LastShotTime = GetWorld()->GetTimeSeconds();
	}
}
