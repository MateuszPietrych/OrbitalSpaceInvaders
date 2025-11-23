// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Projectile.h"
#include "Interface/Resetable.h"
#include "Asteroid.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAsteroidDeathSignature, FVector, DeathLocation, int, AsteroidLevel);

/**
 * 
 */
UCLASS()
class BYTESPACEINVADERS_API AAsteroid : public AProjectile, public IResetable
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void TakeDamage_Implementation(FDamageContext DamageContext) override;
	virtual float GetDamage_Implementation() override;

	virtual void Reset_Implementation() override;

	UPROPERTY(BlueprintAssignable)
	FOnAsteroidDeathSignature OnAsteroidDeath;
	
	UFUNCTION(BlueprintCallable)
	void SetLevel(int NewLevel);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Asteroid, meta = (AllowPrivateAccess = "true"))
	int Level = 1;


};
