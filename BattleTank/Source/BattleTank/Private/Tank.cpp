// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Components/InputComponent.h"
#include "TankMovementComponent.h"
#include "Engine/Engine.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointers added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimComponent"));
	TankMoveComp = CreateDefaultSubobject<UTankMovementComponent>(TEXT("TankMoveComp"));
}

void ATank::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	BarrelRef = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() 
{
	// Protects a nullptr from crashing editor.
	if (!ProjectileBlueprint) 
	{
		UE_LOG(LogTemp, Warning, TEXT("A projectile must be assigned in the Tank Blueprint"))
		return;
	}

	bool bCanFire = (GetWorld()->GetTimeSeconds() - LastShotTime) > FireCooldown;
	if (BarrelRef && bCanFire)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, BarrelRef->GetSocketLocation(FName("BarrelTip")), BarrelRef->GetSocketRotation(FName("BarrelTip")));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastShotTime = GetWorld()->GetTimeSeconds();
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

