// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ByteSpaceInvadersUserWidget.generated.h"


class UUIController;
/**
 * 
 */
UCLASS()
class BYTESPACEINVADERS_API UByteSpaceInvadersUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetUIController(UUIController* NewUIController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UUIController> UIController;
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void UIControllerSet();
};
