// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AlchemyTroubleLibrary.h"
#include "AlchemyTroubleGameModeBase.generated.h"

/**
 * 
 */
UCLASS(minimalapi)
class AAlchemyTroubleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAlchemyTroubleGameModeBase();


protected:
	/** 
	* By adding the database to the game mode makes it assesable throught the game 
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory System")
	class UItemData* ItemDatabase;

public:
	/**
	* This function is for in blueprints == BlueprintNativeEvent = 
	* partially defined in C++ and partially in Blueprint.
	* Allows us to call the event in blueprints but implemntation is done is C++ 
	*/

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory System")
	FItemStruct FindItem(int32 ItemID, bool& Success);

	FItemStruct FindItem_Implementation(int32 ItemID, bool& Success);
	
};
