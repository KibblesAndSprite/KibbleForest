// Fill out your copyright notice in the Description page of Project Settings.


#include "AlchemyTroubleGameModeBase.h"

AAlchemyTroubleGameModeBase::AAlchemyTroubleGameModeBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = AAlchemyTroubleGameModeBase::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	//static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_AlchemyTroublePlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

/** 
* Checks through the database to check if ItemID is in the database and then returns the item.
*/ 
FItemStruct AAlchemyTroubleGameModeBase::FindItem_Implementation(int32 ItemID, bool& Success)
{
	Success = false;

	FItemStruct Item;

	if (ItemDatabase == nullptr)
	{
		return Item;
	}

	for (int i = 0; i < ItemDatabase->Data.Num(); i++)
	{
		if (ItemDatabase->Data[i].ItemID == ItemID)
		{
			Success = true;
			return ItemDatabase->Data[i];
		}
	}

	return Item;
}
