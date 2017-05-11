// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"

UTankMovementComponent::UTankMovementComponent() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

void UTankMovementComponent::MoveForward(float Throw) {
	float ClampedThrow = FMath::Clamp(Throw, -1.0f, 1.0f);
	UE_LOG(LogTemp, Warning, TEXT("Move Forward: %f"), ClampedThrow)
}

void UTankMovementComponent::MoveRight(float Throw) {
	float ClampedThrow = FMath::Clamp(Throw, -1.0f, 1.0f);
	UE_LOG(LogTemp, Warning, TEXT("Move Right: %f"), ClampedThrow)
}