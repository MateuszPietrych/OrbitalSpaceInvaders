// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LinkedListElement.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class ULinkedListElement : public UInterface
{
	GENERATED_BODY()
	
};


class BYTESPACEINVADERS_API ILinkedListElement
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="LinkedListElement")
	TScriptInterface<ILinkedListElement> GetNextElement();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="LinkedListElement")
	void SetNextElement(const TScriptInterface<ILinkedListElement> &NewNextElement);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="LinkedListElement")
	bool HasNextElement();


};
