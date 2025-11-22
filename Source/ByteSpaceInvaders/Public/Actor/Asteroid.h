// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Projectile.h"
#include "Asteroid.generated.h"

/**
 * 
 */
UCLASS()
class BYTESPACEINVADERS_API AAsteroid : public AProjectile
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void TakeDamage_Implementation(FDamageContext DamageContext) override;
	virtual float GetDamage_Implementation() override;

private:
	UFUNCTION(BlueprintCallable)
	void SpawnChilds();

	UFUNCTION(BlueprintCallable)
	FTransform CreateNewTransform();

	UFUNCTION(BlueprintCallable)
	AAsteroid* SpawnChild();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Asteroid, meta = (AllowPrivateAccess = "true"))
	int Level = 1;


};
