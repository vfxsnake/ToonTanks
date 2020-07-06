// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"


// forward declaration to avoid intrisec includes of componenets 
// Capsule componene already exists and is for siple collition. refer to:
// https://docs.unrealengine.com/en-US/API/Runtime/Engine/Components/UCapsuleComponent/index.html
class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();

	void PawnDestroyed();


private:
	// this parameters will be initialized in bluprint.
	// Capsule comonent for main root and collisions;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent * CapsuleComp;
	
	// components to add on the PawnBase,  everything needs the property to add fucntionality.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;
	
	// health component:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent; 
	// attaching the projectile to pawn, as it's going to be selected in blueprint, will use the tSubclass notatnio
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Projectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;

	// pointer to particle sistem:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects", meta=(AllowPrivateAccess="true"))
	USoundBase* DeathSound;

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

	virtual void HandleDestruction();

};

