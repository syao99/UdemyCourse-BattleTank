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
		GetControlledTank()->FirePrimary();
	}
}

ATank* ATankAIController::GetControlledTank() const {
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (ControlledTank) { return ControlledTank; }
	else { return nullptr; }
}

ATank* ATankAIController::GetPlayerTank() const {
	//return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank) { return PlayerTank; }
	else { return nullptr; }
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay(); // Call the BeginPlay() method we're inheriting from first!
}