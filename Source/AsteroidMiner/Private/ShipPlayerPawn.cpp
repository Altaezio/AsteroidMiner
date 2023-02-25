// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipPlayerPawn.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <EnhancedInputComponent.h>
#include <ShipPlayerController.h>

// Sets default values
AShipPlayerPawn::AShipPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Sphere);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(Sphere);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
}

// Called to bind functionality to input
void AShipPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	AShipPlayerController* SPC = Cast<AShipPlayerController>(Controller);

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(SPC->GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(SPC->InputMapping, 0);


	PEI->BindAction(SPC->InputMining, ETriggerEvent::Triggered, this, &AShipPlayerPawn::StartMining);
	PEI->BindAction(SPC->InputModifySpeed, ETriggerEvent::Triggered, this, &AShipPlayerPawn::ModifySpeed);
	PEI->BindAction(SPC->InputOrientHead, ETriggerEvent::Triggered, this, &AShipPlayerPawn::OrientHead);
	PEI->BindAction(SPC->InputRotation, ETriggerEvent::Triggered, this, &AShipPlayerPawn::Rotate);
}

void AShipPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(MoveSpeed * FVector::ForwardVector);
}

void AShipPlayerPawn::StartMining(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello, start to mine please"));
}

void AShipPlayerPawn::ModifySpeed(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Modify your speed !!"));
	if (Controller == nullptr) return;

	const float MoveValue = Value.Get<float>();

	MoveSpeed += MoveValue * ModificationRate;

	if (MoveSpeed < 0.f) MoveSpeed = 0.f;
}

void AShipPlayerPawn::OrientHead(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Where are you looking at ??"));
	if (Controller == nullptr) return;

	FRotator Input(Value[1], Value[0], Value[2]);
	Input *= GetWorld()->GetDeltaSeconds() * RotationScale;
	AddActorLocalRotation(Input);
}

void AShipPlayerPawn::Rotate(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Aww so cute when he turns his head"));
	if (Controller == nullptr) return;

	const float LookValue = Value.Get<float>();

	if (LookValue != 0.f)
	{
		AddActorLocalRotation(FRotator(0, 0, LookValue * GetWorld()->GetDeltaSeconds() * RotationScale));
	}
}
