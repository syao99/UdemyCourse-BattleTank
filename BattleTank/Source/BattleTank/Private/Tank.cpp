// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankTrack.h"
#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// no pointer protection at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	CurrentBarrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
	CurrentTurret = TurretToSet;
}

void ATank::FirePrimary() {
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeSeconds;
	if (!CurrentBarrel || !isReloaded) { return; }
	if (isReloaded) {
		// spawn AProjectile at barrel muzzle socket
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			CurrentBarrel->GetSocketLocation(FName("Muzzle")),
			CurrentBarrel->GetSocketRotation(FName("Muzzle"))
		);
		UE_LOG(LogTemp, Warning, TEXT("%f: Firing Main Cannon! Spawn shell at %s :: %s"), GetWorld()->GetTimeSeconds(), *CurrentBarrel->GetSocketLocation(FName("Muzzle")).ToString(), *CurrentBarrel->GetSocketRotation(FName("Muzzle")).ToString())
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
	
}

void ATank::AimAt(FVector HitLocation) {
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}