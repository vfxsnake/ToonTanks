// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

/**
 * 
 */
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
	void CheckFireCondition();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Conbat", meta=(AllowPrivateAcces = "true"))
	float FireRate = 2.0f;
	FTimerHandle FireRateTimerHandle;

protected:

};
