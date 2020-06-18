// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

// forward declaration to avoid intrisec includes of componenets 
// Capsule componene already exists and is for siple collition. refer to:
// https://docs.unrealengine.com/en-US/API/Runtime/Engine/Components/UCapsuleComponent/index.html
class UCapsuleComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();


private:
	// this parameters will be initialized in bluprint.
	// Capsule comonent for main root and collisions;
	UPROPERTY(VisibleAnywhere, Category="Components", meta=(AllowPrivateAcces=""))
	UCapsuleComponent * CapsuleComp;
	
	// components to add on the PawnBase,  everything needs the property to add fucntionality.
	UPROPERTY(VisibleAnywhere, Category="Components", meta=(AllowPrivateAcces=""))
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere, Category="Components", meta=(AllowPrivateAcces=""))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category="Components", meta=(AllowPrivateAcces=""))
	USceneComponent* ProjectileSpawnPoint;
};

