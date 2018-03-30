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

void ATank::InitializeComponents(UTankAimingComponent * SetAimComp, UTankMovementComponent * SetMoveComp)
{
	AimComp = SetAimComp;
	MoveComp = SetMoveComp;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

