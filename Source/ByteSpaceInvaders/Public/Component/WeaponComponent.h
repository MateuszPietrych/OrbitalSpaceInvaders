// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "WeaponComponent.generated.h"

class AProjectile;
class USceneComponent;
/**
 * 
 */
UCLASS(ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class BYTESPACEINVADERS_API UWeaponComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void SpawnProjectile(TSubclassOf<AProjectile> ProjectileClass, float Damage);

private:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName ProjetileSocketName = TEXT("Projetile");

};
