// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

// forward declarations:
class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

private:
	// pointer to Porjectile component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UProjectileMovementComponent* ProjectileMovement;

	// pointer to static component ("projectile objec in the scene")
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* ProjectileMesh;

	/// this just for reference and demsotration porposes!! ignore
	//using a Template class to defime  the damage type, UDamageType alredi exists in the system.
	// UClass* will be removed. right now is just for clarity porposes.
	// using this syntax inside unreal you can asign any type of class to this pointer.
	// UPROPERTY(EditDefaultsOnly, Category="Damage", meta=(AllowPrivateAccess="true"))
	// UClass* PointerToDamageType; 

	// using TsubClass prevents to use other type of class diferent to UDamageType like the example above.
	UPROPERTY(EditDefaultsOnly, Category="Damage", meta=(AllowPrivateAccess="true"))
	TSubclassOf<UDamageType> DamageType;

	//projectile movement Speed:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement", meta=(AllowPrivateAccess="true"))
	float MovementSpeed = 1300.0f;
	
	// amount of damage agregated:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage", meta=(AllowPrivateAccess="true"))
	float Damage = 50.0f;

	// Effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects", meta=(AllowPrivateAccess="true"))
	UParticleSystem* HitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects", meta=(AllowPrivateAccess="true"))
	USoundBase* HitSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects", meta=(AllowPrivateAccess="true"))
	USoundBase* LaunchSound;

	// Dynamic delegate Function
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
