// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank()
{
    // here you must define the cunstrctor other wise will not work.
    // inerithing spring arm and camera:
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);
    
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
     // calling Rotate and Move class functions
    Rotate();
    Move();
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    // bind to the input components previsuly created in the project prefernci input MoveForward, Turn
    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput); // binding similar to Qt button connection just passing the reference
                                                                                        // to the addres of the fucntion.
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput); // binding to Turn

}


void APawnTank::CalculateMoveInput(float Value)
{
    UE_LOG(LogTemp, Warning, TEXT("Calculating Move multiplied by: %f"), Value);

    // local variable to stor the push force and the set to direction as x component of FVector

    float ForwardPush = Value * MoveSpeed * GetWorld()->DeltaTimeSeconds;  // delta time seconds is a float valuen not a function
    MoveDirection = FVector( ForwardPush, 0,0);
}

void APawnTank::CalculateRotateInput(float Value)
{
    UE_LOG(LogTemp, Warning, TEXT("Calculating Move multiplied by: %f"), Value);
    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation = FRotator(0, RotateAmount, 0);
    RotationDirection = FQuat(Rotation);
}


void APawnTank::Move()
{
    AddActorLocalOffset(MoveDirection, true); // investigate AddActor LocalOfset
    
}

void APawnTank::Rotate()
{
    AddActorLocalRotation(RotationDirection, true);
}
