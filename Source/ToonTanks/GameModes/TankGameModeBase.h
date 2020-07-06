// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

//forward declaration
class APawnTurret;
class APawnTank;
class APlayerControllerBase;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);
	
	UFUNCTION(BlueprintImplementableEvent)	
	void GameStart();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

private:

	// stores the number of turrets to destoy
	int32 TargetTurrets = 0;
	int32 GetTargetTurretCount();

	// reference to player controller:
	APlayerControllerBase* PlayerControllerRef;

	//stores the player tank pointer:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Player", meta=(AllowPrivateAccess="true"))
	APawnTank* PlayerTank;

	// stores the cont down time
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Loop", meta = (AllowPrivateAccess = "true"))
	int StartDelay = 3; // not usin int 32 becaus of bluprints dont handle 32 integerts for performace issues.

	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

	

protected:
	virtual void BeginPlay() override;
	
};
