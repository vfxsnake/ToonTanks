// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Actors/ProjectileBase.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp; // root componene already exist in the class. why not use setRootComponent() function?
	// SetRootComponent(CapsuleComp);  //not sure if it works 

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent); // set as parent the imput of the function
	// by the previus anotation maybe posible to use:
	// BaseMesh->SetupAttachment(GetRootComponent()) // not sure if it works

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh); // set as parent the imput of the function

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}


void APawnBase::RotateTurret(FVector LookAtTarget)
{
	// Udate TurretMesh rotation to face towards the lookAtTarget passed in from the child Class
	// TurretMesh->SetWorldRotation()

	FVector StartLocation = TurretMesh->GetComponentLocation();
	FVector TargetLocation = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FRotator TurretRotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation); // find what it does and why using because is part of blue prints
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
	if(ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{}