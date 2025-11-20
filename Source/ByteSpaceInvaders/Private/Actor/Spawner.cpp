// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Spawner.h"
#include "Utility/UtilityBlueprintFunctionLibrary.h"
#include "Actor/Orbit.h"
#include "Actor/OrbitalShip.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawner::SpawnStartObritalShips()
{
	AOrbit* FirstOrbit = UUtilityBlueprintFunctionLibrary::GetFirstOrbit(this);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (!PlayerPawn) return;

    FVector PlayerLocation = PlayerPawn->GetActorLocation();

	AOrbit* CurrentOrbit = FirstOrbit;

	if(!CurrentOrbit)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnStartObritalShips: FirstOrbit is null"));
		return;
	}

	for(int EnemyCountOnOrbit : StartWave.EnemiesOnOrbits)
	{
		FRotator Rotation = FRotator::ZeroRotator;
		FActorSpawnParameters SpawnParams = FActorSpawnParameters();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
		for(int i=0; i<EnemyCountOnOrbit; i++)
		{
			AOrbitalShip* SpawnedShip = GetWorld()->SpawnActor<AOrbitalShip>(EnemyShipClass, PlayerLocation, Rotation, SpawnParams);
			if(SpawnedShip == nullptr) break;
			SpawnedShip->SetRadiusLength(CurrentOrbit->GetRadius());
			Rotation += FRotator(0.0f, 360.0f/EnemyCountOnOrbit, 0.0f);
		}
		TScriptInterface<ILinkedListElement> NextElement = ILinkedListElement::Execute_GetNextElement(CurrentOrbit);
		CurrentOrbit = Cast<AOrbit>(NextElement.GetObject());
	}

}
