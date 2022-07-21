// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Item.h"

// Sets default values
AInteractable_Item::AInteractable_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

	Trigger->OnComponentBeginOverlap.AddUniqueDynamic(this, &AInteractable_Item::BeginOverlap);
	Trigger->OnComponentEndOverlap.AddUniqueDynamic(this, &AInteractable_Item::EndOverlap);

}

// Called when the game starts or when spawned
void AInteractable_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable_Item::OnItemInteract_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("On Interact"));
	if (bItemCollected) return;

	if (PlayerCharacter != nullptr)
	{
		if (PlayerCharacter->HasFreeInventorySlot())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Item Added"));
			PlayerCharacter->AddItem(ItemID);
			bItemCollected = true;
			OnItemCollected();
		}
	}
}

void AInteractable_Item::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("OverlapCalled"));
	PlayerCharacter = Cast<AAlchemyTroubleCharacter>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->OnEnterActor(this);
	}
}


void AInteractable_Item::EndOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->OnLeaveActor();
	}
}

