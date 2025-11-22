// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boundry.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBoundryDetection, ABoundry*, Boundry, AActor*, DetectedActor);

class USceneComponent;
class UBoxComponent;

UCLASS()
class BYTESPACEINVADERS_API ABoundry : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoundry();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetNewBoundry(FVector NewBoundrySize, bool bNewIsHorizontal);

	bool GetIsHorizontal();

	UPROPERTY(BlueprintCallable)
	FOnBoundryDetection OnBoundryDetection;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> BaseSceneComponent;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoundryBox;

	UPROPERTY()
	bool bIsHorizontal = false;

};
