// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	void dummyfunction();

	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

	// Forward force per track.
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ForwardSpeed = 35000000.f;

	
};
