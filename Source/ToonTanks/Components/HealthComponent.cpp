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

	// Health = DefaultHealth; // this is removed from here because is the constructor, and it is call when youplace the object
	// in the scene so even if is a value that can be modified, it will remain as default as the code says
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// getting the reference as ATankGame mode base from the world. this is for calling the game over and on hit behavior
	GameModeRef = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	Health = DefaultHealth; //here it takes acount of the value setted in blue print as the game starts.
	
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
	UE_LOG(LogTemp, Error, TEXT("current healt: %f ****************"), Health);
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Error, TEXT("health remaning: %f ##########"), Health);
	
	// action if actor die:
	if (Health ==0)
	{
		UE_LOG(LogTemp, Error, TEXT("heald is: %f from %s"), Health, *Owner->GetName());
		if(GameModeRef)
		{
			UE_LOG(LogTemp, Error, TEXT("%s has die"), *Owner->GetName());
			GameModeRef->ActorDied(Owner);
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("no reference to GameMode from Health component")) ;
		}
		
	}
}

