// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/OrbitalShip.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "TimerManager.h"

#include "Component/HealthComponent.h"
#include "Component/WeaponComponent.h"
#include "DataAsset/OrbitalShipDataAsset.h"
#include "Actor/Orbit.h"



// Sets default values
AOrbitalShip::AOrbitalShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = BaseSceneComponent;

	RotatingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RotatingSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RotatingSphere->SetupAttachment(RootComponent);

	// CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// CollisionSphere->SetupAttachment(RotatingSphere);

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ShipMesh->SetupAttachment(RotatingSphere);

	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovement->RotationRate = FRotator(0.0f, 0.0f, 0.0f);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	WeaponComponent->SetupAttachment(ShipMesh);
}

// Called when the game starts or when spawned
void AOrbitalShip::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->InitializeHealthComponent(ShipData->ShipHealth);
	HealthComponent->OnActorDeath.AddDynamic(this, &AOrbitalShip::ShipDeath);
}

// Called every frame
void AOrbitalShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsSmoothSpeedChangeOn)
	{
		ChangeSpeedSmoothTick();
	}

	if(bIsSmoothRadiusChangeOn)
	{
		ChangeRadiusSmoothTick();
	}

}

// Called to bind functionality to input
void AOrbitalShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AOrbitalShip::TakeDamage_Implementation(float DamageAmount)
{
	HealthComponent->ApplyDamage(DamageAmount);
}

float AOrbitalShip::GetDamage_Implementation()
{
	return ShipData->ShipDamage;
}

void AOrbitalShip::InitializeShip(AOrbit* NewOrbit)
{
	CurrentOrbit = NewOrbit;
	SetRadiusLength(CurrentOrbit->GetRadius());
}

void AOrbitalShip::ChangeSpeed(float NewSpeed)
{
	float FinalNewSpeed = FMath::Clamp(NewSpeed, -ShipData->MaxSpeed, ShipData->MaxSpeed);
	RotatingMovement->RotationRate = FRotator(0.0f, FinalNewSpeed, 0.0f);
}

void AOrbitalShip::ChangeSpeedSmooth(float NewSpeed)
{
	StartSpeed = RotatingMovement->RotationRate.Yaw;
	EndSpeed = NewSpeed;
	bIsSmoothSpeedChangeOn = true;
}

void AOrbitalShip::ChangeSpeedSmoothTick()
{
	TimeInChangeSpeed += 0.01f;

	float ChangeSpeedTransitionTime = ShipData->ChangeSpeedTransitionTime;
	float Alpha = FMath::Min(TimeInChangeSpeed/ChangeSpeedTransitionTime, 1.0f);
	float NewSpeed = FMath::Lerp(StartSpeed, EndSpeed, Alpha);

	ChangeSpeed(NewSpeed);

	if(Alpha >= 1)
	{
		bIsSmoothSpeedChangeOn = false;
		StartSpeed = 0.0f;
	}
}

void AOrbitalShip::AddSpeed(float AddSpeed, float AccelerationModifier, float DecelerationModifier)
{
	float CurrentSpeed = RotatingMovement->RotationRate.Yaw;
	bool bCurrentSpeedPositive = CurrentSpeed >= 0;
	bool bAddSpeedPositive = AddSpeed >= 0;
	float SpeedModifier = bCurrentSpeedPositive == bAddSpeedPositive? AccelerationModifier : DecelerationModifier;
	float FinalAddSpeed = AddSpeed * SpeedModifier;
	ChangeSpeed(CurrentSpeed + FinalAddSpeed);
}

void AOrbitalShip::ChangeRadiusSmooth(float RadiusLength)
{
	StartRadius = RotatingSphere->GetScaledSphereRadius();
	EndRadius = RadiusLength;
	bIsSmoothRadiusChangeOn = true;
}

void AOrbitalShip::ChangeRadiusSmoothTick()
{
	TimeInRadiusChange += 0.01f;

	float ChangeSpeedTransitionTime = ShipData->ChangeSpeedTransitionTime;
	float Alpha = FMath::Min(TimeInRadiusChange/ChangeSpeedTransitionTime, 1.0f);
	float NewRadius = FMath::Lerp(StartRadius, EndRadius, Alpha);

	SetRadiusLength(NewRadius);

	if(Alpha >= 1)
	{
		bIsSmoothRadiusChangeOn = false;
		StartRadius = 0.0f;
	}
}

void AOrbitalShip::SetRadiusLength(float RadiusLength)
{
	if(RotatingSphere==nullptr || ShipMesh==nullptr)
		return;
	RotatingSphere->SetSphereRadius(RadiusLength);
	ShipMesh->SetRelativeLocation(FVector(0.0f, RadiusLength, 0.0f));
}

void AOrbitalShip::LowerOrbit()
{
	CurrentOrbit = CurrentOrbit->GetNextOrbit();
	ChangeRadiusSmooth(CurrentOrbit->GetRadius());
}


void AOrbitalShip::ChangeDirection()
{
	float CurrentSpeed = RotatingMovement->RotationRate.Yaw;
	ChangeSpeedSmooth(-CurrentSpeed);
}

void AOrbitalShip::ShipDeath(AActor* DeadActor)
{
	Destroy();
}

void AOrbitalShip::FireProjectile()
{
	WeaponComponent->SpawnProjectile(ShipData->ProjectileClass, ShipData->ShipDamage);
}


