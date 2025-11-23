// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Shield.h"
#include "Component/HealthComponent.h"

// Sets default values
AShield::AShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void AShield::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->InitializeHealthComponent(StartHp);
}

// Called every frame
void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShield::TakeDamage_Implementation(FDamageContext DamageContext)
{
	HealthComponent->ApplyDamage(DamageContext.DamageValue);
	if(HealthComponent->IsDead())
	{
		ShieldDestruction();
	}
}

float AShield::GetDamage_Implementation()
{
    return 0.0f;
}

void AShield::Reset_Implementation()
{
	ShieldReset();
}

