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
	FEnemyWave() {}
	FEnemyWave(TArray<int> NewEnemiesOnOrbits) : EnemiesOnOrbits(NewEnemiesOnOrbits) {}

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

USTRUCT(BlueprintType)
struct FPhysicalScreenBoundry
{
	GENERATED_BODY()

public:
	void SetPhysicalScreenBoundry(FVector NewTopLeftCorner, FVector NewTopRightCorner, FVector NewDownLeftCorner, FVector NewDownRightCorner)
	{
		TopLeftCorner = NewTopLeftCorner;
		TopRightCorner = NewTopRightCorner;
		DownLeftCorner = NewDownLeftCorner;
		DownRightCorner = NewDownRightCorner;
		MiddleTop = (TopLeftCorner+TopRightCorner)/2;
		MiddleDown = (DownLeftCorner+DownRightCorner)/2;
		MiddleLeft = (TopLeftCorner-DownLeftCorner)/2;
		MiddleRight = (TopRightCorner-DownRightCorner)/2;
		Length = FVector::Dist(TopLeftCorner, TopRightCorner);
		Height = FVector::Dist(TopLeftCorner, DownLeftCorner);
	}

	UPROPERTY()
	FVector TopLeftCorner;

	UPROPERTY()
	FVector TopRightCorner;

	UPROPERTY()
	FVector DownLeftCorner;

	UPROPERTY()
	FVector DownRightCorner;

	UPROPERTY()
	FVector MiddleTop;

	UPROPERTY()
	FVector MiddleDown;

	UPROPERTY()
	FVector MiddleLeft;

	UPROPERTY()
	FVector MiddleRight;

	UPROPERTY()
	float Length;

	UPROPERTY()
	float Height;
};

USTRUCT(BlueprintType)
struct FLocationAndLevel
{

	GENERATED_BODY()
	
public:
	FLocationAndLevel(){}
	FLocationAndLevel(FVector NewLocation, int NewLevel) : Location(NewLocation), Level(NewLevel) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level;
};

USTRUCT(BlueprintType)
struct FPeriodEffectForEndless
{

	GENERATED_BODY()
	
public:
	float GetValueOnLevel(int Level, bool bBottomBoundry)
	{
		float ValueOnLevel = StartValue + AdditionalEffectPerLevel * Level;
		float ClampedValue = bBottomBoundry? 
								FMath::Clamp(ValueOnLevel, Boundry, ValueOnLevel):
								FMath::Clamp(ValueOnLevel, ValueOnLevel, Boundry);
		return ClampedValue;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Boundry = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartValue = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AdditionalEffectPerLevel = 1.0f;
};
