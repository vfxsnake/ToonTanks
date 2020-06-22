// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"  // this allow to use timers.

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, 
                                            FireRate, true, false);
}

void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Rotate();
    // Move();
}

void APawnTurret::CheckFireCondition()
{
    // if player == null || is Dead the Bail

    // if Player is in range the Fire
}