// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include <EnhancedInputLibrary.h>
#include "ShipPlayerPawn.generated.h"

UCLASS()
class ASTEROIDMINER_API AShipPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AShipPlayerPawn();

protected:
	UPROPERTY(EditAnywhere)
		class USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere)
		class USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere)
		class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UFloatingPawnMovement* Movement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ModificationRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RotationScale;

	void StartMining(const FInputActionValue& Value);
	void ModifySpeed(const FInputActionValue& Value);
	void OrientHead(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);

public:
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};
