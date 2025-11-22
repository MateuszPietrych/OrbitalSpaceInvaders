// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OrbitalShipDataAsset.generated.h"


class AProjectile;
/**
 * 
 */
UCLASS()
class BYTESPACEINVADERS_API UOrbitalShipDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float ShipHealth = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float ShipDamage = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float MaxSpeed = 180.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float ChangeSpeedTransitionTime = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float ChangeRadiusTransitionTime = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	TSubclassOf<AProjectile> ProjectileClass;


};
