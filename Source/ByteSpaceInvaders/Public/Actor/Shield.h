// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Combat.h"
#include "Interface/Resetable.h"
#include "Shield.generated.h"

class UHealthComponent;

UCLASS()
class BYTESPACEINVADERS_API AShield : public AActor, public ICombat, public IResetable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShield();

	virtual void TakeDamage_Implementation(FDamageContext DamageContext) override;
	virtual float GetDamage_Implementation() override;

	virtual void Reset_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void ShieldDestruction();

	UFUNCTION(BlueprintImplementableEvent)
	void ShieldReset();


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	float StartHp;

};
