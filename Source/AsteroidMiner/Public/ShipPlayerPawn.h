// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class UInputMappingContext* InputMapping;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UFLoatingPawnMovement* Movement;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float MoveScale;

	void MoveForward(const FInputActionValue& Value);

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
