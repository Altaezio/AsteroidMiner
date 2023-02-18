// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShipController.generated.h"

UCLASS()
class ASTEROIDMINER_API AShipController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShipController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UInputMappingContext* InputMapping;

	class USpringArmComponent* SpringArmComp;

	class UCameraComponent* CameraComp;

	void MoveForward(float InputAxis);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
