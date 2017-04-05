// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"




void UTankTrack::SetThrottle(float Throttle) {
	// todo: clamp throttle value!

	UE_LOG(LogTemp, Warning, TEXT("%s Throttle at %f"), *GetName(), Throttle)
}