// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController Tick"))
	auto PlayerTarget = GetPlayerTank();
	if (PlayerTarget) {
		GetControlledTank()->AimAt(PlayerTarget->GetActorLocation());
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	//return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank) { return PlayerTank; }
	else { return nullptr; }
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay(); // Call the BeginPlay() method we're inheriting from first!
	UE_LOG(LogTemp, Warning, TEXT("AIController Begin Play"))

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Current AITank: %s"), *ControlledTank->GetName())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No AITank possessed."))
	}
	// todo: log player tank acquired
	// something something if pointer: log GetPlayerTank()

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Hello Dave. Targeting Player Tank: %s"), *PlayerTank->GetName())
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Cannot find PlayerTank."))
	}
}