// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	/*
	FString CurrentTankName = GetOwner()->GetName();
	FVector BarrelLocation = GetBarrelReference()->GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *CurrentTankName, *HitLocation.ToString(), *BarrelLocation.ToString())
	*/
	
	if (!Barrel) { return; }
	if (!Turret) { return; }
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
		//UE_LOG(LogTemp, Warning, TEXT("Have Aiming Solution: %s"), *AimDirection.ToString())
	}
	else {
		/*FVector CameraLocation;
		FRotator CameraRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			CameraLocation, // GetPlayerViewPoint() sets these vars to their values
			CameraRotation // GetPlayerViewPoint() sets these vars to their values
		);
		FVector CameraDirection = CameraRotation.Vector();
		MoveBarrelTowards(CameraDirection);*/
		//UE_LOG(LogTemp, Warning, TEXT("Does not Have Aiming Solution: %s"), *CameraDirection.ToString())
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

UTankBarrel* UTankAimingComponent::GetBarrelReference() {
	if (!Barrel) { return nullptr; }
	return Barrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

UTankTurret* UTankAimingComponent::GetTurretReference() {
	if (!Turret) { return nullptr; }
	return Turret;
}

void UTankAimingComponent::MoveBarrelTowards(FVector VectorOrientation) {
	MoveBarrelTowards(VectorOrientation.Rotation());
	// TODO review this architecture and see if it's really needed
}

void UTankAimingComponent::MoveBarrelTowards(FRotator RotatorOrientation) {
	// interpolate range of movement limitations and apply to RotatorOrientation

	// figure out difference between current barrel orientation and destination barrel orientation
	FRotator CurrentBarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator DestinationRotator = RotatorOrientation - CurrentBarrelRotator;

	Barrel->Elevate(DestinationRotator.Pitch); // degrees per second ToDo: refactor from magic number

	//FRotator CurrentTurretRotator = Turret->GetForwardVector().Rotation();
	//FRotator DestinationTurretRotator = RotatorOrientation - CurrentTurretRotator;

	Turret->Rotate(DestinationRotator.Yaw);
	// given max rotation speed and frame time, figure out how much to move the barrel this frame

	// draw debug line or something for destination orientation
}