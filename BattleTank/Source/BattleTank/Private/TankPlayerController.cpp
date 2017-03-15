// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

/*
	ontick
		super
		aimtowardscrosshair()

*/

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController Tick"))
	AimAtCrosshair();
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay(); // Call the BeginPlay() method we're inheriting from first!
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"))

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Current PlayerTank: %s"), *ControlledTank->GetName())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No PlayerTank possessed."))
	}
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // out parameter!
	if (bGetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
		// TODO: controlled tank needs to aim at HitLocation
	}
	// get world location of line trace thru crosshair
	// if hits object
		// set controlled tank aim to point
}

bool ATankPlayerController::bGetSightRayHitLocation(FVector& out_HitLocation) const {

	/*
	find crosshair position
	de-project screen position of crosshair to a world direction
	line trace and see what's hit (up to max range)

	*/

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = GetScreenLocation(ViewportSizeX, ViewportSizeY);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString())


	FVector CameraWorldLocation;
	FVector WorldDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, WorldDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *WorldDirection.ToString())
	}
	
	
	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
	//	CameraViewPointLocation,
	//	CameraViewPointRotation
	//);

	/*
		
		get player's camera location
		get player's camera rotation
		create ray from player's camera
		test for collision with actor
		return collision point

	*/


	out_HitLocation = FVector(0.1f);
	return true;
}

FVector2D ATankPlayerController::GetScreenLocation(int32 ViewportSizeX, int32 ViewportSizeY) const {
	FVector2D ScreenLocation = FVector2D(
		ViewportSizeX * CrosshairXLocation,
		ViewportSizeY * CrosshairYLocation
	);
	return ScreenLocation;
}