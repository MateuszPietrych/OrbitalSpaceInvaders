// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ByteSpaceInvadersStructures.generated.h"

USTRUCT(BlueprintType)
struct FEnemyWave
{
	GENERATED_BODY()

public:
	//First element is number of enemies on the most far orbit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> EnemiesOnOrbits;

};