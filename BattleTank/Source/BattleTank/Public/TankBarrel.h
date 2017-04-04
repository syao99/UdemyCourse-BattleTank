// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RelativeSpeed); // relative speed is a multiplier: -1 to 1

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 20;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevation = 0;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevation = 30;
};
