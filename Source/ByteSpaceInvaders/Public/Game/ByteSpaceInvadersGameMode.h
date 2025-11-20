// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ByteSpaceInvadersGameMode.generated.h"

class AOrbit;
/**
 * 
 */
UCLASS()
class BYTESPACEINVADERS_API AByteSpaceInvadersGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetFirstOrbit(AOrbit* NewFirstOrbit);

	UFUNCTION(BlueprintCallable)
	AOrbit* GetFirstOrbit();

private:
	UPROPERTY()
	TObjectPtr<AOrbit> FirstOrbit;
	
};
