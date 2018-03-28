// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	// UE_LOG(LogTemp, Warning, TEXT("%s throttle is %f"), *Name, Throttle);

	FVector ForceApplied = GetForwardVector() * Throttle * ForwardSpeed;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
