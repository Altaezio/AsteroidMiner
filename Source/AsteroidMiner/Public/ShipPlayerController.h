// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShipPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROIDMINER_API AShipPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere)
		class UInputAction* InputMining;
	UPROPERTY(EditAnywhere)
		class UInputAction* InputModifySpeed;
	UPROPERTY(EditAnywhere)
		class UInputAction* InputOrientHead;
	UPROPERTY(EditAnywhere)
		class UInputAction* InputRotation;
};
