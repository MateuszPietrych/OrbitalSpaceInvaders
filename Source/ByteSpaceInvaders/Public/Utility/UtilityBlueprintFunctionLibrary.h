// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilityBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BYTESPACEINVADERS_API UUtilityBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static AByteSpaceInvadersGameMode* GetByteSpaceInvadersGameMode(UObject* ContextObject);

	UFUNCTION(BlueprintCallable)
	static AOrbit* GetFirstOrbit(UObject* ContextObject);
	
};
