// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"  // this allow to use timers.
#include "PawnTank.h"

void APawnTurret::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, 
                                            FireRate, true, false);

    // storing the Player PawnTank: GetPlayerPawn first input is  who is calling it
    // second is the player index 

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0)); 
}

void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!PlayerPawn || ReturnDistanceToPlayer()> FireRange)
    {
        return;
    }

    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
    // if player == null || is Dead the Bail
    // find ou if player is balid:
    if(!PlayerPawn)
    {
        return;
    }


    // if Player is in range the Fire
    if (ReturnDistanceToPlayer() <= FireRange)
    {
       Fire();
    }

    // else
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("Player Out of range from %s"), *GetName());
    // }
}

float APawnTurret::ReturnDistanceToPlayer()
{
    if(!PlayerPawn)
    {   

        return 0.0f;
    }

    float Distance = (PlayerPawn->GetActorLocation() - GetActorLocation()).Size(); //Size returns the magnitud of the vector. see FVector::Size()
    return Distance;
}

void APawnTurret::HandleDestruction()
{
    Super::HandleDestruction(); 
    Destroy(); // function from Queued thread Pools you can fine it by controll click the function.
}