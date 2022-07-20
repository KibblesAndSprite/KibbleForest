// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AlchemyTroubleCharacter.h"
#include "AlchemyTroublePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AAlchemyTroublePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAlchemyTroublePlayerController();

protected:
	virtual void BeginPlay() override; // added for inventory
	virtual void SetupInputComponent() override;
	void GetThrowDirection();

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);


// ======================= INVENTORY =======================
public:
	class AAlchemyTroubleCharacter* MyCharacter;

protected:
	UFUNCTION()
	void Interact();

	UFUNCTION()
	void SwitchItem();
};
