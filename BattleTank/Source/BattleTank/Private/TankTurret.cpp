// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeRotationSpeed)
{
	RelativeRotationSpeed = FMath::Clamp<float>(RelativeRotationSpeed, -1, 1);
	auto RotationChange = RelativeRotationSpeed * TurretRotationRate * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}


