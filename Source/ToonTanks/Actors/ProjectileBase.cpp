// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // the tick component wont be use so this is for performace optimization. 

	// adding the components to class as a default component for the class
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;

	 // from AActor.h member variable  float, sets the life span of an actor.
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Calling On Hit"));
	AActor* MyOwner = GetOwner();
	if(!MyOwner)
	{
		return;
	}

	if (OtherActor !=NULL && OtherActor != this && OtherActor != MyOwner) //avoid sef collision and owner collision.
	{
		// using the kismet game statics iclude funcitons aply damage to the other actor
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType); // investigate this function latter.
		UE_LOG(LogTemp, Warning, TEXT("Applying damage "));
	}

	/* here we are going to implemente fx aned stuff!!
	.........................................
	*/
	
	// calling the destroy funciton
	UE_LOG(LogTemp, Warning, TEXT("Destroy Actor"));
	Destroy(); // this funciton must be from the actor class

}

