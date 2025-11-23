// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Resetable.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class UResetable : public UInterface
{
	GENERATED_BODY()
};


class BYTESPACEINVADERS_API IResetable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Reset")
	void Reset();
};
