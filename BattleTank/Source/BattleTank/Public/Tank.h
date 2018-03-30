// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"

// Forward declarations
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void decoy();

	// Run this function on BeginPlay in blueprint to ensure all C++ functions can access the tanks components and their functions.
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitializeComponents(UTankAimingComponent* SetAimComp, UTankMovementComponent* SetMoveComp);
	UTankAimingComponent* AimComp;
	UTankMovementComponent* MoveComp;

protected:

private:	
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
