// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainGameplayPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AOrbitalShip;
/**
 * 
 */
UCLASS()
class BYTESPACEINVADERS_API AMainGameplayPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay();
	
private:
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Fire(const FInputActionValue& Value);



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY()
	TObjectPtr<AOrbitalShip> PlayerShip;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float BaseSpeedChangeOnMove = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float AccelerationModifier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float DecelerationModifier = 1.0f;
};
