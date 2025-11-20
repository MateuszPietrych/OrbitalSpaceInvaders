// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/OrbitalShip.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "TimerManager.h"

#include "Component/HealthComponent.h"
#include "DataAsset/OrbitalShipDataAsset.h"



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
}

// Called when the game starts or when spawned
void AOrbitalShip::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->InitializeHealthComponent(ShipData->ShipHealth);
}

// Called every frame
void AOrbitalShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void AOrbitalShip::ChangeSpeed(float NewSpeed)
{
	RotatingMovement->RotationRate = FRotator(0.0f, NewSpeed, 0.0f);
}

void AOrbitalShip::ChangeSpeedSmooth(float NewSpeed)
{
	StartSpeed = RotatingMovement->RotationRate.Yaw;
	EndSpeed = NewSpeed;
	GetWorld()->GetTimerManager().SetTimer(SmoothChangeSpeedTimer, this, &AOrbitalShip::ChangeSpeedSmoothTick, 0.01f, true);
}

void AOrbitalShip::ChangeSpeedSmoothTick()
{
	TimeInChangeSpeed += 0.01f;
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if(!TimerManager.IsTimerActive(SmoothChangeSpeedTimer))
	{
		UE_LOG(LogTemp, Warning, TEXT("SmoothChangeSpeedTimer Not Active"));
		return;
	}

	float ChangeSpeedTransitionTime = ShipData->ChangeSpeedTransitionTime;
	float Alpha = FMath::Min(TimeInChangeSpeed/ChangeSpeedTransitionTime, 1.0f);
	float NewSpeed = FMath::Lerp(StartSpeed, EndSpeed, Alpha);

	ChangeSpeed(NewSpeed);

	if(Alpha >= 1)
	{
		TimerManager.ClearTimer(SmoothChangeSpeedTimer);
		StartSpeed = 0.0f;
	}
}

void AOrbitalShip::AddSpeed(float AddSpeed)
{
	float CurrentSpeed = RotatingMovement->RotationRate.Yaw;
	ChangeSpeed(CurrentSpeed + AddSpeed);
}

void AOrbitalShip::ChangeRadiusSmooth(float RadiusLength)
{
	StartRadius = RotatingSphere->GetScaledSphereRadius();
	EndRadius = RadiusLength;
	GetWorld()->GetTimerManager().SetTimer(SmoothChangeRadiusTimer, this, &AOrbitalShip::ChangeRadiusSmoothTick, 0.01f, true);
}

void AOrbitalShip::ChangeRadiusSmoothTick()
{
	TimeInRadiusChange += 0.01f;
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if(!TimerManager.IsTimerActive(SmoothChangeSpeedTimer))
	{
		UE_LOG(LogTemp, Warning, TEXT("SmoothChangeSpeedTimer Not Active"));
		return;
	}

	float ChangeSpeedTransitionTime = ShipData->ChangeSpeedTransitionTime;
	float Alpha = FMath::Min(TimeInRadiusChange/ChangeSpeedTransitionTime, 1.0f);
	float NewRadius = FMath::Lerp(StartRadius, EndRadius, Alpha);

	SetRadiusLength(NewRadius);

	if(Alpha >= 1)
	{
		TimerManager.ClearTimer(SmoothChangeRadiusTimer);
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


