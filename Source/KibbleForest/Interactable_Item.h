// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Interface_Interactable.h"
#include "AlchemyTroubleCharacter.h"
#include "Interactable_Item.generated.h"

UCLASS()
class KIBBLEFOREST_API AInteractable_Item : public AActor, public IInterface_Interactable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive")
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive")
	class UBoxComponent* Trigger;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ===================== INTERACTIVE =====================

protected:
	AAlchemyTroubleCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bItemCollected;


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Events")
	void OnItemCollected();

public:

	// Interaface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item Interact")
	void OnItemInteract();

	//Actual implementation of the Interact event
	void OnItemInteract_Implementation();

protected:
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
