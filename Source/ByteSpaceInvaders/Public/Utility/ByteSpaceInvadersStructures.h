// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ByteSpaceInvadersStructures.generated.h"


//////////////////////////////// ENUMS //////////////////////////////

UENUM(BlueprintType) 
enum class EDamageType : uint8
{
    Projectile      UMETA(DisplayName = "Projectile"),
    Direct       UMETA(DisplayName = "Direct"),
};

UENUM(BlueprintType) 
enum class EUIHealthChangeActors : uint8
{
    Earth      UMETA(DisplayName = "Earth"),
    Player       UMETA(DisplayName = "Player"),
};

UENUM(BlueprintType) 
enum class EGameState : uint8
{
    Running      UMETA(DisplayName = "Running"),
    Won       UMETA(DisplayName = "Won"),
	Lost       UMETA(DisplayName = "Lost"),
	Paused       UMETA(DisplayName = "Paused"),
};


//////////////////////////////// STRUCTS //////////////////////////////

USTRUCT(BlueprintType)
struct FEnemyWave
{
	GENERATED_BODY()

public:
	//First element is number of enemies on the most far orbit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> EnemiesOnOrbits;

};

USTRUCT(BlueprintType)
struct FDamageContext
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageType DamageType;
};