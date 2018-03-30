// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Classes/Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;


UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank * GetControlledTank() const;
	void AimTowardCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector, FVector&) const;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairX = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairY = 0.3333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;
};
