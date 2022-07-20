// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AlchemyTroubleLibrary.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EKey_QuestItems				UMETA(DisplayName = "Quest Items"),
	EUsable_Consumables			UMETA(DisplayName = "Consumables"),
	EUsable_Throwables			UMETA(DisplayName = "Throwables"),
	EUsable_Placeables			UMETA(DisplayName = "Placeables"),
	EWorld_Interactable			UMETA(DisplayName = "interactable"),
	EWorld_NonInteractable		UMETA(DisplayName = "Non-interactable")
};

// ========ITEMS=========
USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_USTRUCT_BODY()

	// Item ID used to find item in the database
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	int32 ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText ItemDescription;

	// The max allowed in each slot 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 NumberOfAllowedItems;

	// Enum holding all types of items
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	EItemType ItemType;

	// Item that will appear in the inventory
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class AActor> ItemActor;

	// Icon for UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UTexture2D* ItemIcon;

	//==========INVENTORY=========

	// This is the item on the player
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	AActor* SpawnedItem;

	// This is the amount in the inventory
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 AmountInInventory;

};

UCLASS(BlueprintType)
class UItemData : public UDataAsset
{
	GENERATED_BODY()

public:

	// Change later to a TMap
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	TArray<FItemStruct> Data;


};



/**
 * 
 */
class KIBBLEFOREST_API AlchemyTroubleLibrary
{
public:
	AlchemyTroubleLibrary();
	~AlchemyTroubleLibrary();
};
