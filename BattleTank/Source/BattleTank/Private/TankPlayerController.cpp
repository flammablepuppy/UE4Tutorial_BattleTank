// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank."))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is currently possessed by player."), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// PASSED CHECK: UE_LOG(LogTemp, Warning, TEXT("Ticking."))
	// Aim at crosshair
	AimTowardCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }
	
	FVector HitLocation; // Out parameter
		if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// TODO Tell controlled tank to aim at this point.

	}
}

// Get world location of linetrace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position
	int32 ViewportX; int32 ViewportY;
	GetViewportSize(ViewportX, ViewportY);

	auto ScreenLocation = FVector2D(ViewportX * CrosshairX, ViewportY * CrosshairY);
	// PASSED CHECK: UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	// De-project the crosshair screen position
	// Linetrace along that direction, see what we hit (to a max range)
	return true;
}