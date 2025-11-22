// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Asteroid.h"


void AAsteroid::BeginPlay()
{
    FVector NewScale = FVector(Level,Level,Level);
    SetActorScale3D(NewScale);
}

void AAsteroid::TakeDamage_Implementation(FDamageContext DamageContext)
{
    if(Level > 1) SpawnChilds();
    Destroy();
}

float AAsteroid::GetDamage_Implementation()
{
    return Level;
}

FTransform AAsteroid::CreateNewTransform()
{
    FVector Location = GetActorLocation();
    float RandomYaw = FMath::FRandRange(0.f, 360.f);
    FRotator RandomRotation(0.f, RandomYaw, 0.f);
    FVector Scale(Level, Level, Level);
    FTransform NewTransform(RandomRotation, Location, Scale);
    return NewTransform;
}

AAsteroid* AAsteroid::SpawnChild()
{
    FTransform SpawnTransform = CreateNewTransform();
    FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
    AAsteroid* Child = GetWorld()->SpawnActor<AAsteroid>(AAsteroid::StaticClass(), SpawnTransform, SpawnParams);
    return Child;
}

void AAsteroid::SpawnChilds()
{
    AAsteroid* Child1 = SpawnChild();
    AAsteroid* Child2 = SpawnChild();
}