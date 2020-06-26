// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
    // Super::BeginPlay(); not sure right now if it needs to be called

     // Get references and game win/lose condition

     //Call handleGameStart to initilalise the start countdown, turret activation, pawn check etc.
    
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
    //Check what type of actor died. If Turret, tally. if Player-> go to loose condition
    UE_LOG(LogTemp, Warning, TEXT("this actor has died: %s"), *DeadActor->GetName());
}

void ATankGameModeBase::HandleGameStart()
{
    // call blueprint version gemstart(); and initilises the game.

}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
    // see player has won or loose
    // if turret won show lose result.
    // Call blueprintVersion gameOver();
}