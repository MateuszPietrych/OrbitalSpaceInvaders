// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Orbit.h"
#include "Earth.generated.h"

class UHealthComponent;
class UHpVisualsDataAsset;
/**
 * 
 */
UCLASS()
class BYTESPACEINVADERS_API AEarth : public AOrbit
{
	GENERATED_BODY()

	AEarth();

public:
	UHealthComponent* GetEarthHealthComponent();
	UHpVisualsDataAsset* GetHpVisualsDataAsset();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UHpVisualsDataAsset* HpVisualsDataAsset;
};
