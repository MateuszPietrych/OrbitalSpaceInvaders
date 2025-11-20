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
	float ShipHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float ShipDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement)
	float ChangeSpeedTransitionTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
	TSubclassOf<AProjectile> ProjectileClass;


};
