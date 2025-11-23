// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/UIController.h"
#include "Actor/Earth.h"
#include "Actor/OrbitalShip.h"
#include "Component/HealthComponent.h"
#include "DataAsset/HpVisualsDataAsset.h"
#include "Utility/ByteSpaceInvadersStructures.h"
#include "Utility/UtilityBlueprintFunctionLibrary.h"
#include "Actor/EnemyManager.h"
#include "Controller/MainGameplayPlayerController.h"
#include "Game/ByteSpaceInvadersGameMode.h"

void UUIController::SetWidgetControllerParams(const FUIControllerParams& UICParams)
{
    PlayerShip = UICParams.PlayerShip;
    Earth = UICParams.Earth;
    PlayerController = UICParams.PlayerController;
    EnemyManager = UICParams.EnemyManager;
}

AOrbitalShip* UUIController::GetPlayerShip()
{
    return PlayerShip;
}

AEarth* UUIController::GetEarth()
{
    return Earth;
}

AMainGameplayPlayerController* UUIController::GetPlayerController()
{
    return PlayerController;
}

AEnemyManager* UUIController::GetEnemyManager()
{
    return EnemyManager;
}

void UUIController::BindCallbacksToDependencies()
{
    GetEarth()->GetEarthHealthComponent()->OnHealthChange.AddUniqueDynamic(this, &UUIController::HandleEarthHealthChange);
    GetPlayerShip()->GetOrbitalShipHealthComponent()->OnHealthChange.AddUniqueDynamic(this, &UUIController::HandlePlayerHealthChange);
    GetPlayerController()->OnPauseGame.AddUniqueDynamic(this, &UUIController::HandlePauseGame);
    GetEnemyManager()->OnDestroyingLastEnemy.AddUniqueDynamic(this, &UUIController::HandleDestroyingLastEnemy);
}

void UUIController::HandlePlayerHealthChange(float CurrentHealth, float MaxHealth)
{
    HandleHealthChange(CurrentHealth, MaxHealth, EUIHealthChangeActors::Player);
}

void UUIController::HandleEarthHealthChange(float CurrentHealth, float MaxHealth)
{
    HandleHealthChange(CurrentHealth, MaxHealth, EUIHealthChangeActors::Earth);
}

void UUIController::HandleHealthChange(float CurrentHealth, float MaxHealth, EUIHealthChangeActors ActorType)
{
    OnHealthChangeController.Broadcast(CurrentHealth, MaxHealth, ActorType);
    if(CurrentHealth <= 0.0f)
    {
        OnChangeGameState.Broadcast(EGameState::Lost);
    }
}

void UUIController::HandlePauseGame(bool bPaused)
{
    EGameState NewGameState = bPaused? EGameState::Paused : EGameState::Running;
    OnChangeGameState.Broadcast(NewGameState);
}

void UUIController::HandleDestroyingLastEnemy()
{
    OnChangeGameState.Broadcast(EGameState::Won);
}

UHpVisualsDataAsset* UUIController::GetHpVisualDataAsset(EUIHealthChangeActors ActorType)
{
    switch(ActorType)
    {
        case EUIHealthChangeActors::Earth:
            return GetEarth()->GetHpVisualsDataAsset();
        case EUIHealthChangeActors::Player:
            return GetPlayerShip()->GetHpVisualsDataAsset();
    }
    return nullptr;
}

void UUIController::ResumeGame(EGameState PreviousState)
{
    AByteSpaceInvadersGameMode* GameMode = UUtilityBlueprintFunctionLibrary::GetByteSpaceInvadersGameMode(this);
    switch(PreviousState)
    {
        case EGameState::Won:
            GameMode->ResetGame();
            break;
        case EGameState::Lost:
            GameMode->ResetGame();
            break;
    }
}

void UUIController::ResetGame()
{
 
}