// Fill out your copyright notice in the Description page of Project Settings.


#include "AlchemyTroublePlayerController.h"

AAlchemyTroublePlayerController::AAlchemyTroublePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AAlchemyTroublePlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyCharacter = Cast<AAlchemyTroubleCharacter>(GetPawn());
}

void AAlchemyTroublePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("BeginThrow", IE_Pressed, this, &AAlchemyTroublePlayerController::GetThrowDirection);

	InputComponent->BindAxis("MoveX", this, &AAlchemyTroublePlayerController::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AAlchemyTroublePlayerController::Move_YAxis);

// ======================= INVENTORY =============================
	InputComponent->BindAction("Interact", IE_Released, this, &AAlchemyTroublePlayerController::Interact);
	InputComponent->BindAction("SwitchItem", IE_Released, this, &AAlchemyTroublePlayerController::SwitchItem);

}

void AAlchemyTroublePlayerController::GetThrowDirection()
{
	// Casts a line trace from the camera to whatever he area underneath the cursor is and retrieves the location of the hit.
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), true, HitResult);

	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z);
	APawn* const MyPawn = GetPawn();
	// Ensures that the player can't overthrow the item.
	FVector DirectionalVector = FVector(FMath::Clamp(HitResult.Location.X - MyPawn->GetActorLocation().X, -100.0f, 100.0f),
		FMath::Clamp(HitResult.Location.Y - MyPawn->GetActorLocation().Y, -100.0f, 100.0f),
		FMath::Clamp(HitResult.Location.Z - MyPawn->GetActorLocation().Z, -100.0f, 100.0f)
	);
	
	ThrowItem( DirectionalVector + GetPawn()->GetActorLocation() );
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), DirectionalVector.X, DirectionalVector.Y, DirectionalVector.Z);
}

void AAlchemyTroublePlayerController::ThrowItem(FVector SpawnPoint) 
{
	FActorSpawnParameters SpawnParams;

	AUsableItem* ActorRef = GetWorld()->SpawnActor<AUsableItem>(UsableItem, SpawnPoint, GetPawn()->GetActorRotation(), SpawnParams);

	if (ActorRef) {
		UE_LOG(LogTemp, Warning, TEXT("Actor Spawned"));
	}
		
	else
		UE_LOG(LogTemp, Warning, TEXT("Actor Not Spawned"));


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

// ======================= INVENTORY =======================

// input actions
void AAlchemyTroublePlayerController::Interact()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("ACTION"));
	if (MyCharacter != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("ACTION"));
		MyCharacter->Interact();
	}
}

void AAlchemyTroublePlayerController::SwitchItem()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("SWITCH"));
	if (MyCharacter != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SWITCH"));
		MyCharacter->SwitchItem();
	}
}

void AAlchemyTroublePlayerController::FreeHands()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("FREE"));
	if (MyCharacter != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("FREE"));
		MyCharacter->FreeHands();
	}
}

