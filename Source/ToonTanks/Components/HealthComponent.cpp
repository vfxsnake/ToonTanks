// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "../GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Health = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// getting the reference as ATankGame mode base from the world. this is for calling the game over and on hit behavior
	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	Owner = GetOwner();
	if(Owner)
	{
		// adding the dynamic bindin:
		/// dynamic binding means that it adds the functionality only when the game begins.
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No reference to  owner in health component"));
	}
	
	
}

void UHealthComponent::TakeDamage(AActor* DamageActor, float Damage, const class UDamageType* DamageType, 
									class AController* InstigateBy, AActor* DamageCauser)
{
	if(Damage == 0 || Health == 0)
	{
		return;
	}

	// setting heald
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	// action if actor die:
	if (Health <=0)
	{
		if(GameModeRef)
		{
			GameModeRef->ActorDied(Owner);
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("no reference to GameMode from Health component")) ;
		}
		
	}
}

