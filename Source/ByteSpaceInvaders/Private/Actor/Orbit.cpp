// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Orbit.h"
#include "Components/SphereComponent.h"

// Sets default values
AOrbit::AOrbit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OrbitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = OrbitSphere;
}

// Called when the game starts or when spawned
void AOrbit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOrbit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TScriptInterface<ILinkedListElement> AOrbit::GetNextElement_Implementation()
{
	return NextOrbit;
}

void AOrbit::SetNextElement_Implementation(const TScriptInterface<ILinkedListElement> &NewNextElement)
{
	NextOrbit = NewNextElement;
}

bool AOrbit::HasNextElement_Implementation()
{
	return NextOrbit.GetObject() == nullptr;
}

float AOrbit::GetRadius()
{
	return OrbitSphere->GetScaledSphereRadius();
}

void AOrbit::AddShipToOrbit(AOrbitalShip* Ship)
{
	ShipsOnOrbit.Add(Ship);
}

void AOrbit::RemoveShipFromOrbit(AOrbitalShip* Ship)
{
	ShipsOnOrbit.Remove(Ship);
}