// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h" // this is a library for the interface
#include "AlchemyTroubleLibrary.h"
#include "AlchemyTroubleGameModeBase.h"
#include "Interface_Interactable.h"
#include "AlchemyTroubleCharacter.generated.h"

UCLASS(Blueprintable)
class AAlchemyTroubleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAlchemyTroubleCharacter();

	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// ==================== INVENTORY ============
public:
	// Where the item will be held on the player 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* CarryItemPoint;

protected:
	// Players Inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Inventory")
	TArray<FItemStruct> Inventory;

	// Maximun slots in inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Inventory")
	int32 TotalItemSlots = 10;

	// Checks if the item is equipped
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Inventory")
	bool bItemEquipped = false;

	// Where item is in slot...which slot the item is in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Inventory")
	int32 IndexItemEquipped;

	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Inventory")
	int32 ItemIDEquipped;

// ============== Interactive ======================

	AActor* CurrentInteractiveActor;
	IInterface_Interactable* CurrentInteractive;

public:
	/**
	* These are used for the interactables like items 
	*/
	void OnEnterActor(AActor* InteractiveActor);

	void OnLeaveActor();


	// ========= INVENTORY =======
	void AddItem(int32 ItemID);

	void RemoveItem(int32 ItemID, bool RemoveItem);

	bool HasFreeInventorySlot();

	bool HasItemEquippded(int32 ItemID);

	void Interact();

	void SwitchItem();

	void FreeHands();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Event")
	void RefreshInventory();


};
