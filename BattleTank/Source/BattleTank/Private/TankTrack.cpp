// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"




void UTankTrack::SetThrottle(float Throttle) {
	// todo: clamp throttle value!
	float ClampedThrottle = FMath::Clamp(Throttle, -1.0f, 1.0f);
	FVector ForceApplied = GetForwardVector() * ClampedThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	UE_LOG(LogTemp, Warning, TEXT("%s Throttle Force %s at %s"), *GetName(), *ForceApplied.ToString(), *ForceLocation.ToString())
}