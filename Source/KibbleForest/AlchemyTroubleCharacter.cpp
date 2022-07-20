// Fill out your copyright notice in the Description page of Project Settings.


#include "AlchemyTroubleCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

// Sets default values
AAlchemyTroubleCharacter::AAlchemyTroubleCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

}

// Called when the game starts or when spawned
void AAlchemyTroubleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAlchemyTroubleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAlchemyTroubleCharacter::OnEnterActor(AActor* InteractiveActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Enter Actor"));
	if (InteractiveActor != nullptr)
	{
		// checks if actor is using the interatable interface
		bool IsInterface = UKismetSystemLibrary::DoesImplementInterface(InteractiveActor, UInterface_Interactable::StaticClass());
		if (IsInterface)
		{
			CurrentInteractiveActor = InteractiveActor;
			CurrentInteractive = Cast<IInterface_Interactable>(InteractiveActor);

		}
	}
}

void AAlchemyTroubleCharacter::OnLeaveActor()
{
	CurrentInteractive = nullptr;
	CurrentInteractiveActor = nullptr;
}


// ====INVENTORY=======

void AAlchemyTroubleCharacter::AddItem(int32 ItemID)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("AddItem"));
	// Adding to the inventory
	for (int i = 0; i < Inventory.Num(); i++)
	{
		// checks if item is in inventory and adds 1 if true
		if (Inventory[i].ItemID == ItemID)
		{
			Inventory[i].AmountInInventory += 1;

			if (!bItemEquipped)
			{
				IndexItemEquipped = i;
				ItemIDEquipped = ItemID;
				bItemEquipped = true;

				Inventory[i].SpawnedItem->SetActorHiddenInGame(false);

			}

			RefreshInventory();
			return;
		}
	}

	if (Inventory.Num() == TotalItemSlots)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Inventory Full"));
	}

	// finds the item in the database on the gamemode
	AAlchemyTroubleGameModeBase* GameMode = Cast<AAlchemyTroubleGameModeBase>(GetWorld()->GetAuthGameMode()); // Check if better way then cast
	if (GameMode != nullptr)
	{
		bool Found = false;
		FItemStruct ItemFound = GameMode->FindItem(ItemID, Found);

		if (Found && (ItemFound.ItemActor != nullptr))
		{
			AActor* SpawnItem = GetWorld()->SpawnActor<AActor>(ItemFound.ItemActor, FVector::ZeroVector, FRotator::ZeroRotator);

			// Adds item to our list
			if (SpawnItem != nullptr)
			{
				FItemStruct NewItem;
				NewItem.ItemID = ItemID;
				NewItem.ItemName = ItemFound.ItemName;
				NewItem.ItemDescription = ItemFound.ItemDescription;
				NewItem.AmountInInventory = 1;
				NewItem.ItemIcon = ItemFound.ItemIcon;
				NewItem.SpawnedItem = SpawnItem;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("AddItemToInventory"));
				Inventory.Add(NewItem);

			}
		}
	}

	RefreshInventory();
}


void AAlchemyTroubleCharacter::RemoveItem(int32 ItemID, bool RemoveItem)
{
	// find the item we want to remove //
	int32 ItemToRemove = -1; // removes one from the inventory 
	for (int i = 0; i < Inventory.Num(); i++)
	{
		// checks if item is in inventory and adds 1 if true
		if (Inventory[i].ItemID == ItemID)
		{
			Inventory[i].AmountInInventory -= 1;
			if (Inventory[i].AmountInInventory <= 0)
			{
				ItemToRemove = i;

				if (bItemEquipped && (ItemIDEquipped == ItemID))
				{
					IndexItemEquipped = -1;
					ItemIDEquipped = 0;
					bItemEquipped = false;
				}
			}
			else if (RemoveItem)
			{
				FreeHands();
			}

			break;
		}
	}

	// if all items are remove from inventory remove from list 
	if (ItemToRemove >= 0)
	{
		Inventory[ItemToRemove].SpawnedItem->Destroy(); //Destroys the reference 
		Inventory.RemoveAt(ItemToRemove); // remove from list
	}

	RefreshInventory();
}

bool AAlchemyTroubleCharacter::HasFreeInventorySlot()
{
	return (Inventory.Num() < TotalItemSlots);
}

bool AAlchemyTroubleCharacter::HasItemEquippded(int32 ItemID)
{
	if (bItemEquipped)
	{
		return (ItemID == ItemIDEquipped);
	}

	return false;
}

void AAlchemyTroubleCharacter::Interact()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ACTION"));
	if (CurrentInteractive != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ACTION"));
		// Execute the interact event on the blueprint of the actor
		IInterface_Interactable::Execute_OnInteract(CurrentInteractiveActor);
	}
}

void AAlchemyTroubleCharacter::SwitchItem()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Switch"));
	if (Inventory.Num() == 0) return;

	if (!bItemEquipped)
	{
		IndexItemEquipped = 0;
		Inventory[IndexItemEquipped].SpawnedItem->SetActorHiddenInGame(false);

		bItemEquipped = true;
		ItemIDEquipped = Inventory[IndexItemEquipped].ItemID;

		return;
	}
}

void AAlchemyTroubleCharacter::FreeHands()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Free"));
	if (bItemEquipped && (IndexItemEquipped >= 0) && (IndexItemEquipped < Inventory.Num()))
	{
		Inventory[IndexItemEquipped].SpawnedItem->SetActorHiddenInGame(true);
	}

	IndexItemEquipped = -1;
	bItemEquipped = false;
	ItemIDEquipped = 0;
}

