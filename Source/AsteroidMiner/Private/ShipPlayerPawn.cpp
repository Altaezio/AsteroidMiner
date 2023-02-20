// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipPlayerPawn.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <EnhancedInputComponent.h>

// Sets default values
AShipPlayerPawn::AShipPlayerPawn()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Sphere);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(Sphere);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
}

// Called to bind functionality to input
void AShipPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Get the player controller
	AController* Controller = GetController();

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	PEI->BindAction(InputForward, ETriggerEvent::Triggered, this, &AShipPlayerPawn::MoveForward);
}

void AShipPlayerPawn::MoveForward(const FInputActionValue& Value)
{
	if (Controller == nullptr) return;

	const FVector2D MoveValue = Value.Get<FVector2D>();

	if (MoveValue.Y == 0.f) return;

	// Find out which way is forward
	const FRotator Rotation(0, Controller->GetControlRotation().Yaw, 0);

	// Get forward vector
	const FVector Direction = Rotation.RotateVector(FVector::ForwardVector);
	AddMovementInput(Direction, MoveValue.Y);
}

