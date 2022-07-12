// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AlchemyTroublePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class /*KIBBLEFOREST_API*/ AAlchemyTroublePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAlchemyTroublePlayerController();

protected:
	virtual void SetupInputComponent() override;

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
};
