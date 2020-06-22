// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

/**
 * 
 */

// forward declarations:
class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()
	
public:
	// no need of costructor because is an derivate class ands use the cosntructor of the APawnBase.

	// Called every frame:
	virtual void Tick(float DeltaTime) override;

	// Caled when the game start or when spawned
	virtual void BeginPlay() override;

private:
	//private variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conbat", meta=(AllowPrivateAccess = "true"))
	float FireRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conbat", meta=(AllowPrivateAccess = "true"))
	float FireRange = 500.f; // this is 5 metters. Remember UE mesures are in centimiters

	// handles the timer funciton
	FTimerHandle FireRateTimerHandle;

	// to store the player pawn tank
	APawnTank* PlayerPawn = nullptr;


	// private Methos
	void CheckFireCondition();
	float ReturnDistanceToPlayer();

protected:

};
