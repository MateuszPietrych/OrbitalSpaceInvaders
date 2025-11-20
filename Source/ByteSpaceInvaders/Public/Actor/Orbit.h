// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/LinkedListElement.h"
#include "Orbit.generated.h"

class USphereComponent;
class AOrbitalShip;

UCLASS()
class BYTESPACEINVADERS_API AOrbit : public AActor, public ILinkedListElement
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrbit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual TScriptInterface<ILinkedListElement> GetNextElement_Implementation() override;
	virtual void SetNextElement_Implementation(const TScriptInterface<ILinkedListElement> &NewNextElement) override;
	virtual bool HasNextElement_Implementation() override;

	UFUNCTION(BlueprintCallable)
	float GetRadius();

	UFUNCTION(BlueprintCallable)
	void AddShipToOrbit(AOrbitalShip* Ship);

	UFUNCTION(BlueprintCallable)
	void RemoveShipFromOrbit(AOrbitalShip* Ship);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> OrbitSphere;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OrbitData, meta = (AllowPrivateAccess = "true"))
	TScriptInterface<ILinkedListElement> NextOrbit;

	UPROPERTY()
	TArray<AOrbitalShip*> ShipsOnOrbit; 

};
