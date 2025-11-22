// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ByteSpaceInvadersHUD.generated.h"

class UUIController;
class UByteSpaceInvadersUserWidget;
/**
 * 
 */
UCLASS()
class BYTESPACEINVADERS_API AByteSpaceInvadersHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UUIController* GetUIController(const FUIControllerParams& UICParams);

private:
	UPROPERTY()
	UByteSpaceInvadersUserWidget* OverlayWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UByteSpaceInvadersUserWidget> OverlayWidgetClass;

	UPROPERTY()
	UUIController* WidgetController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUIController> OrbWidgetControllerClass;
};
