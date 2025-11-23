// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Spawner.h"
#include "Utility/ByteSpaceInvadersStructures.h"
#include "EndlessSpawner.generated.h"

/**
 * 
 */
UCLASS()
class BYTESPACEINVADERS_API AEndlessSpawner : public ASpawner
{
	GENERATED_BODY()

public:
	virtual void StartGame(int Level = 1) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	FPeriodEffectForEndless AsteroidTimeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	FPeriodEffectForEndless SpecialEnemyTimeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	FPeriodEffectForEndless EnemySpeedTimeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	FPeriodEffectForEndless EnemyFireSpeedInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	FPeriodEffectForEndless OrbitalEnemyCountInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	int EnemiesOnOrbitMaxCount = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	float MaxGameTime = 300.f;
	
};
