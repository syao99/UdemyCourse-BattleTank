// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void ATankPlayerController::BeginPlay() override;
	ATank* ATankPlayerController::GetControlledTank() const;

private:
	UPROPERTY(EditAnywhere)
	float SightingRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.5f;

	void AimAtCrosshair();

	bool bGetSightRayHitLocation(FVector& out_HitLocation) const;

	FVector2D GetScreenLocation(int32 ViewportSizeX, int32 ViewportSizeY) const;

	FVector CameraViewPointLocation;
	FRotator CameraViewPointRotation;
};
