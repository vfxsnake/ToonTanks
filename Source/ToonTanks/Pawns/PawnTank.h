// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"


// forward declaration:
class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()
	
public:

	APawnTank(); 

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	/*	the class is use becasue your going to pass a class instace, but all declaration are out ofscope, the only way to pass
	this parameter is declaring it inside de parentesis*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; 
	
private:
	// creating components to attach as inherited and displayed in blue print context
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	// varibles to store input muliply:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 250.f;

	FVector MoveDirection;
	FQuat RotationDirection;

	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);

	void Move();
	void Rotate();
};
