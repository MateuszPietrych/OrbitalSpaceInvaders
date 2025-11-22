// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/Combat.h"
#include "OrbitalShip.generated.h"

class UOrbitalShipDataAsset;
class UStaticMeshComponent;
class USphereComponent;
class USceneComponent;
class URotatingMovementComponent;

class UHealthComponent;
class UWeaponComponent;
class UHpVisualsDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShipDeathSignature, AOrbitalShip*, DeadShip);

UCLASS()
class BYTESPACEINVADERS_API AOrbitalShip : public APawn, public ICombat
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AOrbitalShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void TakeDamage_Implementation(FDamageContext DamageContext) override;
	virtual float GetDamage_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void InitializeShip(AOrbit* NewOrbit);

	UFUNCTION(BlueprintCallable)
	void ChangeSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable)
	void ChangeSpeedSmooth(float NewSpeed);

	UFUNCTION()
	void ChangeSpeedSmoothTick();

	UFUNCTION(BlueprintCallable)
	void AddSpeed(float AddSpeed, float AccelerattionModifier = 1.0f, float DecelerationModifier = 1.0f);

	UFUNCTION(BlueprintCallable)
	void ChangeRadiusSmooth(float RadiusLength);

	UFUNCTION()
	void ChangeRadiusSmoothTick();

	UFUNCTION()
	void SetRadiusLength(float RadiusLength);

	UFUNCTION()
	void LowerOrbit();

	UFUNCTION()
	void ChangeDirection();

	UFUNCTION()
	void ShipDeath(AActor* DeadActor);

	UFUNCTION(BlueprintCallable)
	void FireProjectile();

	UHealthComponent* GetOrbitalShipHealthComponent();
	UHpVisualsDataAsset* GetHpVisualsDataAsset();

	UPROPERTY(BlueprintAssignable)
	FOnShipDeathSignature OnShipDeath;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ShipData, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UOrbitalShipDataAsset> ShipData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> BaseSceneComponent;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ShipMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> RotatingSphere;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URotatingMovementComponent> RotatingMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponComponent> WeaponComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UHpVisualsDataAsset* HpVisualsDataAsset;


	TWeakObjectPtr<AOrbit> CurrentOrbit;

	FTimerHandle SmoothChangeSpeedTimer;
	bool bIsSmoothSpeedChangeOn = false;
	float TimeInChangeSpeed = 0.0f;
	float StartSpeed = 0.0f;
	float EndSpeed = 0.0f;

	FTimerHandle SmoothChangeRadiusTimer;
	bool bIsSmoothRadiusChangeOn = false;
	float TimeInRadiusChange = 0.0f;
	float StartRadius = 0.0f;
	float EndRadius = 0.0f;

};
