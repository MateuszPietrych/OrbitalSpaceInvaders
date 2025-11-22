// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Asteroid.h"
#include "GameFramework/ProjectileMovementComponent.h"


void AAsteroid::BeginPlay()
{
    Super::BeginPlay();
    FVector Forward = GetActorForwardVector();
    ProjectileMovement->SetVelocityInLocalSpace(Forward * ProjetileSpeed);
    SetLevel(Level);
}

void AAsteroid::TakeDamage_Implementation(FDamageContext DamageContext)
{
    if(Level > 1) OnAsteroidDeath.Broadcast(GetActorLocation(), Level);
    this->Destroy();
}

float AAsteroid::GetDamage_Implementation()
{
    return Level;
}

void AAsteroid::SetLevel(int NewLevel)
{
    Level = NewLevel;
    FVector NewScale = FVector(Level,Level,Level);
    SetActorScale3D(NewScale);
}
