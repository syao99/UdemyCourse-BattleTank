// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	/*
	FString CurrentTankName = GetOwner()->GetName();
	FVector BarrelLocation = GetBarrelReference()->GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *CurrentTankName, *HitLocation.ToString(), *BarrelLocation.ToString())
	*/
	
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Muzzle"));
	
	bool bHaveAimingSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		false
	);
	if (bHaveAimingSolution) {
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		FString TankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming At: %s"), *TankName, *AimDirection.ToString())
			MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}

UTankBarrel* UTankAimingComponent::GetBarrelReference() {
	return Barrel;
}

void UTankAimingComponent::MoveBarrelTowards(FVector VectorOrientation) {
	MoveBarrelTowards(VectorOrientation.Rotation());
	// TODO review this architecture and see if it's really needed
}

void UTankAimingComponent::MoveBarrelTowards(FRotator RotatorOrientation) {
	// interpolate range of movement limitations and apply to RotatorOrientation

	// figure out difference between current barrel orientation and destination barrel orientation
	FRotator CurrentRotator = Barrel->GetForwardVector().Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("RotatorOrientation: %s"), *CurrentOrientation.ToString())
	FRotator DestinationRotator = RotatorOrientation - CurrentRotator;

	Barrel->Elevate(5); // degrees per second ToDo: refactor from magic number
	// given max rotation speed and frame time, figure out how much to move the barrel this frame


	// draw debug line or something for destination orientation

	// set turret rotation using yaw

	// set barrel elevation using pitch

}