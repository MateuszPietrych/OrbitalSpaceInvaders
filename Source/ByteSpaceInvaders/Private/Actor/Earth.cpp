// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Earth.h"
#include "Component/HealthComponent.h"
#include "DataAsset/HpVisualsDataAsset.h"


AEarth::AEarth()
{
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

UHealthComponent* AEarth::GetEarthHealthComponent()
{
    return HealthComponent;
}

UHpVisualsDataAsset* AEarth::GetHpVisualsDataAsset()
{
    return HpVisualsDataAsset;
}