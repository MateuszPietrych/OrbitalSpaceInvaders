// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Utility/ByteSpaceInvadersStructures.h"
#include "UIController.generated.h"


class AEarth;
class AEnemyManager;
class AOrbitalShip;
class UHpVisualsDataAsset;
class AMainGameplayPlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChangeController, int, CurrentHealth, int, MaxHealth, EUIHealthChangeActors, ActorType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeGameState, EGameState, NewGameState);

USTRUCT(BlueprintType)
struct FUIControllerParams
{
	GENERATED_BODY()

	FUIControllerParams() {}
	FUIControllerParams(AOrbitalShip* PS, AEarth* Ea, AMainGameplayPlayerController* PC, AEnemyManager* EM)
	: PlayerShip(PS), Earth(Ea), PlayerController(PC), EnemyManager(EM) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AOrbitalShip> PlayerShip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AEarth> Earth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AMainGameplayPlayerController> PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AEnemyManager> EnemyManager;
};
/**
 * 
 */
UCLASS()
class BYTESPACEINVADERS_API UUIController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)	
	void SetWidgetControllerParams(const FUIControllerParams& UICParams);

	UFUNCTION(BlueprintCallable)
	AOrbitalShip* GetPlayerShip();

	UFUNCTION(BlueprintCallable)
	AEarth* GetEarth();

	UFUNCTION(BlueprintCallable)
	AMainGameplayPlayerController* GetPlayerController();

	UFUNCTION(BlueprintCallable)
	AEnemyManager* GetEnemyManager();

	UFUNCTION()
	void HandlePlayerHealthChange(int CurrentHealth, int MaxHealth);

	UFUNCTION()
	void HandleEarthHealthChange(int CurrentHealth, int MaxHealth);

	UFUNCTION()
	void HandleHealthChange(int CurrentHealth, int MaxHealth, EUIHealthChangeActors ActorType);

	UFUNCTION()
	void HandlePauseGame(bool bPaused);

	UFUNCTION()
	void HandleDestroyingLastEnemy();

	UFUNCTION(BlueprintCallable)
	void BindCallbacksToDependencies();

	UFUNCTION(BlueprintCallable)
	UHpVisualsDataAsset* GetHpVisualDataAsset(EUIHealthChangeActors ActorType);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeController OnHealthChangeController;
	
	UPROPERTY(BlueprintAssignable)
	FOnChangeGameState OnChangeGameState;

private:
	UPROPERTY()
	TObjectPtr<AOrbitalShip> PlayerShip;

	UPROPERTY()
	TObjectPtr<AEarth> Earth;

	UPROPERTY()
	TObjectPtr<AMainGameplayPlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<AEnemyManager> EnemyManager;
};
