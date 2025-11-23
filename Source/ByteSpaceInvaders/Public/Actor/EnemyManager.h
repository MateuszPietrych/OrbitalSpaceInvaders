// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Resetable.h"
#include "EnemyManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDestroyingLastEnemy);


class AOrbitalShip;

UCLASS()
class BYTESPACEINVADERS_API AEnemyManager : public AActor, public IResetable
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

	virtual void Reset_Implementation() override;

	void FinishSpawningEnemies(TArray<AOrbitalShip*> SpawnedShipList);

	void SetFireCountBase(int FireCount);


	void LowerOrbit();

	void ChangeMovementDirection();

	void AddEnemy(AOrbitalShip* Ship);

	UFUNCTION()
	void RemoveShipFromList(AOrbitalShip* Ship);

	void Fire();

	void ResetEnemyManager();

	FOnDestroyingLastEnemy OnDestroyingLastEnemy;

private:
	float GetTimePeriodBetweenFires();
	int GetFireCount();

	TArray<int> GetRandomEnemyIndexes(int EnemyCount);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyOrbitMovement, meta = (AllowPrivateAccess = "true"))
	float TimeOnSingleOrbit = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = EnemyOrbitMovement, meta = (AllowPrivateAccess = "true"))
	float TimeUntilChangeDirection = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fire, meta = (AllowPrivateAccess = "true"))
	float PeroidBetweenFiresBase = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fire, meta = (AllowPrivateAccess = "true"))
	float MaxRandomChangeToPeroid = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fire, meta = (AllowPrivateAccess = "true"))
	int FireCountBase = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Fire, meta = (AllowPrivateAccess = "true"))
	int MaxRandomFireCountChange = 2;

	UPROPERTY()
	TArray<AOrbitalShip*> OrbitalShips;

	UPROPERTY()
	TSet<AOrbitalShip*> SpecialShips;

	UPROPERTY()
	FTimerHandle LowerOrbitTimer;

	UPROPERTY()
	FTimerHandle ChangeDirectionTimer;

	UPROPERTY()
	FTimerHandle FiresTimer;

};
