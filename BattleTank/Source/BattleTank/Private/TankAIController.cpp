// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ThisAI = Cast<ATank>(GetPawn());
	if (PlayerTank)
	{
		MoveToActor(PlayerTank, MoveAcceptanceRadius);

		ThisAI->AimComp->AimAt(PlayerTank->GetActorLocation());

		ThisAI->AimComp->Fire();
	}
}