// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyingLastEnemy);


class AOrbitalShip;

UCLASS()
class BYTESPACEINVADERS_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FinishSpawningEnemies(TArray<AOrbitalShip*> SpawnedShipList);

	void LowerOrbit();

	void ChangeMovementDirection();

	void AddEnemy(AOrbitalShip* Ship);

	UFUNCTION()
	void RemoveShipFromList(AOrbitalShip* Ship);

	void Fire();

	FOnDestroyingLastEnemy OnDestroyingLastEnemy;

private:
	float GetTimePeriodBetweenFires();
	int GetFireCount();

	TArray<int> GetRandomEnemyIndexes(int EnemyCount);

private:
	UPROPERTY(EditDefaultsOnly, Category = EnemyOrbitMovement)
	float TimeOnSingleOrbit = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = EnemyOrbitMovement)
	float TimeUntilChangeDirection = 5.0f;

	//NOT USED YET - TODO?
	UPROPERTY(EditDefaultsOnly, Category = EnemyOrbitMovement)
	float OrbitalShipsSpeedModifierOnOrbitChange = 1.1f;


	UPROPERTY(EditDefaultsOnly, Category = Fire)
	float PeroidBetweenFiresBase = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = Fire)
	float MaxRandomChangeToPeroid = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = Fire)
	int FireCountBase = 5;

	UPROPERTY(EditDefaultsOnly, Category = Fire)
	int MaxRandomFireCountChange = 2;

	UPROPERTY()
	TArray<AOrbitalShip*> OrbitalShips;

	UPROPERTY()
	FTimerHandle LowerOrbitTimer;

	UPROPERTY()
	FTimerHandle ChangeDirectionTimer;

	UPROPERTY()
	FTimerHandle FiresTimer;

};
