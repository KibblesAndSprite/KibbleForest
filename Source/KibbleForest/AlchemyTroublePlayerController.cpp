// Fill out your copyright notice in the Description page of Project Settings.


#include "AlchemyTroublePlayerController.h"

AAlchemyTroublePlayerController::AAlchemyTroublePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AAlchemyTroublePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveX", this, &AAlchemyTroublePlayerController::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AAlchemyTroublePlayerController::Move_YAxis);
	UE_LOG(LogTemp, Display, TEXT("X"));

}

void AAlchemyTroublePlayerController::Move_XAxis(float AxisValue)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		FVector AffectedVector = FVector(AxisValue, 0, 0);
		//FVector WorldPosition = MyPawn->GetActorLocation().GetSafeNormal() + AffectedVector;
		MyPawn->AddMovementInput(AffectedVector * 1, 1.f, false);
	}
}

void AAlchemyTroublePlayerController::Move_YAxis(float AxisValue)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		FVector AffectedVector = FVector(0, AxisValue, 0);
		//FVector WorldPosition = MyPawn->GetActorLocation().GetSafeNormal() + AffectedVector;
		MyPawn->AddMovementInput(AffectedVector * 1, 1.f, false);
	}
}
