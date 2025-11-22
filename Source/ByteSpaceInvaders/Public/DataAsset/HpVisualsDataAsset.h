// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HpVisualsDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class BYTESPACEINVADERS_API UHpVisualsDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	FColor HpMarkerColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	TObjectPtr<UTexture2D> HpIdentityImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	TObjectPtr<UTexture2D> HpMarkerImage;
};
