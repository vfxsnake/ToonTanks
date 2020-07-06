// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "../Pawns/PawnTank.h"
#include "../Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "../PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{

    TargetTurrets = GetTargetTurretCount();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0)); 

    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

    HandleGameStart();

    Super::BeginPlay(); // not sure right now if it needs to be called

     // Get references and game win/lose condition

     //Call handleGameStart to initilalise the start countdown, turret activation, pawn check etc.
    
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
    if(DeadActor)
    {
        UE_LOG(LogTemp, Error, TEXT("dead actor passed: %s"), *DeadActor->GetName());
        if(APawnTank* DestroyedTank = Cast<APawnTank>(DeadActor))
        {
            UE_LOG(LogTemp, Error, TEXT("inside TankDied, Actor Name : %s"), *DeadActor->GetName());
        
            PlayerTank->PawnDestroyed();
            HandleGameOver(false);

            if (PlayerControllerRef)
            {
                PlayerControllerRef->SetPlayerEnabledState(false);
            }
        }

        else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
        {
            UE_LOG(LogTemp, Error, TEXT("inside Destroyed Turret, Actor Name : %s"), *DestroyedTurret->GetName());
            
            DestroyedTurret->PawnDestroyed();
            
            TargetTurrets --; // substracts 1 to TargetTurrets
            if (TargetTurrets <= 0)
            {
                HandleGameOver(true);
            }
        }
    }

}

void ATankGameModeBase::HandleGameStart()
{
    // call blueprint version gemstart(); and initilises the game.
    GameStart();

    if (PlayerControllerRef)
    {
        PlayerControllerRef->SetPlayerEnabledState(false);
        
        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnableDelegate = 
            FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);

        // seting time handle:
        GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);

    }

}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    // Call blueprintVersion gameOver();
    GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
    TSubclassOf<APawnTurret> ClassToFind;
    ClassToFind = APawnTurret::StaticClass(); // what does static class mean?
    // guessing sends the class thats been instanced

    TArray<AActor*> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, TurretActors); 
    return  TurretActors.Num();

}