// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UObject/NoExportTypes.h"
#include "Combat.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class UCombat : public UInterface
{
	GENERATED_BODY()
};

class BYTESPACEINVADERS_API ICombat
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Combat")
	void TakeDamage(float DamageAmount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Combat")
	float GetDamage();

};
