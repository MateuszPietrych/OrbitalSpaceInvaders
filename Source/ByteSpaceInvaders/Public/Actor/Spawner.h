// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utility/ByteSpaceInvadersStructures.h"
#include "Spawner.generated.h"

class AOrbit;
class AOrbitalShip;
class AEnemyManager;

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
	void SpawnStartObritalShips();

	UFUNCTION()
	TArray<AOrbitalShip*> SpawnOrbitalShipsOnOrbit(int EnemyCountOnOrbit, AOrbit* CurrentOrbit, FVector SpawnLocation);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	FEnemyWave StartWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AOrbitalShip> EnemyShipClass;

	TWeakObjectPtr<AEnemyManager> EnemyManager;



};
