// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MainGameplayPlayerController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Actor/OrbitalShip.h"

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
    }
}

void AMainGameplayPlayerController::BeginPlay()
{
    PlayerShip = Cast<AOrbitalShip>(GetPawn());
}

void AMainGameplayPlayerController::Move(const FInputActionValue& Value)
{
    if(!PlayerShip) return;
    
    PlayerShip->AddSpeed(BaseSpeedChangeOnMove*Value.GetMagnitude(), AccelerationModifier, DecelerationModifier);
}

void AMainGameplayPlayerController::Fire(const FInputActionValue& Value)
{
    if(!PlayerShip) return;

    PlayerShip->FireProjectile();
}