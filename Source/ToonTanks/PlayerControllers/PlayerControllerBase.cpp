// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

// this function will enable or disable the mouse cursor in the game to bee seen
void APlayerControllerBase::SetPlayerEnabledState(bool SetPlayerEnabled)
{
    if(SetPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
        APlayerControllerBase::bShowMouseCursor = true;
    }
    else
    {
        GetPawn()->DisableInput(this);
        APlayerControllerBase::bShowMouseCursor = false;
    }
}