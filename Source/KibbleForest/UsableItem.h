// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "UsableItem.generated.h"

/**
 * 
 */
UCLASS()
class KIBBLEFOREST_API AUsableItem : public AItem
{
	GENERATED_BODY()

public:
	AUsableItem();

protected:
	void UseItem() override;

public:
	int ReturnItemType();

private:
	UPROPERTY(EditAnywhere)
		bool IsConsumable = false;
	UPROPERTY(EditAnywhere)
		bool CanBeThrown = true;
	
};
