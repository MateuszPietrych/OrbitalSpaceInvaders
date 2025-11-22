// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MainGameplayPlayerController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Actor/OrbitalShip.h"
#include "Kismet/GameplayStatics.h"

void AMainGameplayPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainGameplayPlayerController::Move);
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AMainGameplayPlayerController::Fire);
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AMainGameplayPlayerController::PauseGame);
    }
}

void AMainGameplayPlayerController::BeginPlay()
{
    PlayerShip = Cast<AOrbitalShip>(GetPawn());
    PrimaryActorTick.bTickEvenWhenPaused = true;
}

void AMainGameplayPlayerController::Move(const FInputActionValue& Value)
{
    if(!PlayerShip || UGameplayStatics::IsGamePaused(this)) return;
    
    PlayerShip->AddSpeed(BaseSpeedChangeOnMove*Value.GetMagnitude(), AccelerationModifier, DecelerationModifier);
}

void AMainGameplayPlayerController::Fire(const FInputActionValue& Value)
{
    if(!PlayerShip || UGameplayStatics::IsGamePaused(this)) return;

    PlayerShip->FireProjectile();
}

void AMainGameplayPlayerController::PauseGame(const FInputActionValue& Value)
{
    UWorld* World = GetWorld();
    if (!World) return;

    bool bGamePaused = UGameplayStatics::IsGamePaused(this);
    OnPauseGame.Broadcast(!bGamePaused);
    UGameplayStatics::SetGamePaused(World, !bGamePaused);
}