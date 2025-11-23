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
	FPeriodEffectTimeInfo AsteroidTimeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	FPeriodEffectTimeInfo SpecialEnemyTimeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	FPeriodEffectTimeInfo EnemySpeedTimeInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameSetup, meta = (AllowPrivateAccess = "true"))
	FPeriodEffectTimeInfo EnemyFireSpeedInfo;
	
};
