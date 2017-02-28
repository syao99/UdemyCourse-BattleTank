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
	// get world location of line trace thru crosshair
	// if hits object
		// set controlled tank aim to point
}