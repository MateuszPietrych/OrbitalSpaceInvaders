// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ByteSpaceInvadersGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishGameReset);

class AOrbit;
class ASpawner;
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

	UFUNCTION(BlueprintCallable)
	void InitalizeSpawner();

	UFUNCTION()
	void ResetGame();

	UPROPERTY(BlueprintAssignable)
	FOnFinishGameReset GameReset;

private:
	UPROPERTY()
	TObjectPtr<AOrbit> FirstOrbit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASpawner> SpawnerClass;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Level = 1.0f;
	
};
