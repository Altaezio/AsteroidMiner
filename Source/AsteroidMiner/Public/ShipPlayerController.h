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
	virtual void SetUpInputComponent() override;

	UPROPERTY()
		class UInputMappingContext* PawnMappingContext;

	UPROPERTY()
		class UInputAction* InputForward;
};
