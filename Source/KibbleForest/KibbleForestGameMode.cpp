// Copyright Epic Games, Inc. All Rights Reserved.

#include "KibbleForestGameMode.h"
#include "KibbleForestPlayerController.h"
#include "KibbleForestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKibbleForestGameMode::AKibbleForestGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AKibbleForestPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	//static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_AlchemyTroublePlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}