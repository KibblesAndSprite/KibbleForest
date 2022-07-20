// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_Interactable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KIBBLEFOREST_API IInterface_Interactable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface Interact")
	void OnInteract();
};
