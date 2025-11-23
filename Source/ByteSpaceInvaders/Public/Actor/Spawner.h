// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utility/ByteSpaceInvadersStructures.h"
#include "Spawner.generated.h"

class AOrbit;
class AOrbitalShip;
class AEnemyManager;
class AAsteroid;


UCLASS()
class BYTESPACEINVADERS_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void StartGame(int Level = 1);

	UFUNCTION(BlueprintCallable)
	void SpawnStartObritalShips(float SpeedModifier = 1.0f);

	UFUNCTION(BlueprintCallable)
	void SpawnSpecialEnemy();

	UFUNCTION(BlueprintCallable)
	AAsteroid* SpawnAsteroid(FVector SpawnLocation, int AsteroidLevel);

	UFUNCTION(BlueprintCallable)
	void OnAsteroidDeathAsteroid(FVector DeathLocation, int AsteroidLevel);

	UFUNCTION(BlueprintCallable)
	FTransform CreateNewAsteroidTransform(FVector DeathLocation, int Level);

	void TrySpawnSpecialEnemy();

	void TrySpawnAsteroid();

	UFUNCTION(BlueprintImplementableEvent)
	void DelaySpawn();

	UFUNCTION()
	TArray<AOrbitalShip*> SpawnOrbitalShipsOnOrbit(int EnemyCountOnOrbit, AOrbit* CurrentOrbit, float SpeedModifier = 1.0f);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	FEnemyWave StartWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	TArray<float> SpecialEnemySpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	TArray<float> AsteroidSpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AOrbitalShip> EnemyShipClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AOrbitalShip> SpecialEnemyShipClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAsteroid> AsteroidClass;

	TWeakObjectPtr<AEnemyManager> EnemyManager;

	UPROPERTY()
	FVector EnemySpawnLocation;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float GameTime = 0.0f;

	UPROPERTY()
	int SpecialEnemyIndex = 0;

	UPROPERTY()
	int AsteroidIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess ="true"))
	TArray<FLocationAndLevel> LocationsAndLevels;

	UPROPERTY()
	float AsteroidSpawnDelayTime;

};
