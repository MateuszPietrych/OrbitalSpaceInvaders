// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Spawner.h"
#include "Utility/UtilityBlueprintFunctionLibrary.h"
#include "Actor/Orbit.h"
#include "Actor/OrbitalShip.h"
#include "Actor/EnemyManager.h"
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
	AActor* ActorEnemyManager = UGameplayStatics::GetActorOfClass(this, AEnemyManager::StaticClass());
	EnemyManager = Cast<AEnemyManager>(ActorEnemyManager);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
    if (!PlayerPawn) return;
    EnemySpawnLocation = PlayerPawn->GetActorLocation();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameTime += DeltaTime;

	if(SpecialEnemyIndex >= SpecialEnemySpawnTime.Num()) return;
	float CurrentTimeSpawn = SpecialEnemySpawnTime[SpecialEnemyIndex];
	if(!SpecialEnemySpawnTime.IsEmpty() && CurrentTimeSpawn <= GameTime)
	{
		SpawnSpecialEnemy();
		SpecialEnemyIndex++;
	}
}

void ASpawner::SpawnStartObritalShips()
{
	AOrbit* FirstOrbit = UUtilityBlueprintFunctionLibrary::GetFirstOrbit(this);
	AOrbit* CurrentOrbit = FirstOrbit;

	if(!CurrentOrbit)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnStartObritalShips: FirstOrbit is null"));
		return;
	}


	TArray<AOrbitalShip*> SpawnedShipList;
	for(int EnemyCountOnOrbit : StartWave.EnemiesOnOrbits)
	{
		TArray<AOrbitalShip*> SpawnedShipListOnOrbit = SpawnOrbitalShipsOnOrbit(EnemyCountOnOrbit, CurrentOrbit);
		SpawnedShipList.Append(SpawnedShipListOnOrbit);
		CurrentOrbit = CurrentOrbit->GetNextOrbit();
	}
	EnemyManager->FinishSpawningEnemies(SpawnedShipList);
}

TArray<AOrbitalShip*> ASpawner::SpawnOrbitalShipsOnOrbit(int EnemyCountOnOrbit, AOrbit* CurrentOrbit)
{
	FRotator Rotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 

	TArray<AOrbitalShip*> SpawnedShipList;
	for(int i=0; i<EnemyCountOnOrbit; i++)
	{
		AOrbitalShip* SpawnedShip = GetWorld()->SpawnActor<AOrbitalShip>(EnemyShipClass, EnemySpawnLocation, Rotation, SpawnParams);
		if(SpawnedShip == nullptr) break;
		
		SpawnedShip->InitializeShip(CurrentOrbit);
		SpawnedShipList.Add(SpawnedShip);
		Rotation += FRotator(0.0f, 360.0f/EnemyCountOnOrbit, 0.0f);
	}
	
	return SpawnedShipList;
}

void ASpawner::SpawnSpecialEnemy()
{
	FRotator Rotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
	AOrbitalShip* SpawnedShip = GetWorld()->SpawnActor<AOrbitalShip>(EnemyShipClass, EnemySpawnLocation, Rotation, SpawnParams);
	EnemyManager->AddEnemy(SpawnedShip);
}

