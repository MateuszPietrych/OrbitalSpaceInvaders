// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Spawner.h"
#include "Utility/UtilityBlueprintFunctionLibrary.h"
#include "Actor/Orbit.h"
#include "Actor/OrbitalShip.h"
#include "Actor/EnemyManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Actor/Asteroid.h"

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

	TrySpawnSpecialEnemy();
	TrySpawnAsteroid();
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
	AOrbitalShip* SpawnedShip = GetWorld()->SpawnActor<AOrbitalShip>(SpecialEnemyShipClass, EnemySpawnLocation, Rotation, SpawnParams);
	if(!SpawnedShip) return;
	EnemyManager->AddEnemy(SpawnedShip);
}


AAsteroid* ASpawner::SpawnAsteroid(FVector SpawnLocation, int AsteroidLevel)
{
	FTransform SpawnTransform = CreateNewAsteroidTransform(SpawnLocation, AsteroidLevel);
    FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
    AAsteroid* Asteroid = GetWorld()->SpawnActor<AAsteroid>(AsteroidClass, SpawnTransform, SpawnParams);
	if(!Asteroid) 
	{
		return nullptr;
	}

	Asteroid->OnAsteroidDeath.AddDynamic(this, &ASpawner::OnAsteroidDeathAsteroid);
	Asteroid->SetLevel(AsteroidLevel);
	return Asteroid;
}

void ASpawner::OnAsteroidDeathAsteroid(FVector DeathLocation, int AsteroidLevel)
{
	LocationsAndLevels.Add(FLocationAndLevel(DeathLocation, AsteroidLevel-1));
	LocationsAndLevels.Add(FLocationAndLevel(DeathLocation, AsteroidLevel-1));
	DelaySpawn();
}

FTransform ASpawner::CreateNewAsteroidTransform(FVector DeathLocation, int AsteroidLevel)
{
	FVector Location = DeathLocation;
    float RandomYaw = FMath::FRandRange(0.f, 360.f);
    FRotator RandomRotation(0.f, RandomYaw, 0.f);
    FVector Scale(AsteroidLevel, AsteroidLevel, AsteroidLevel);
    FTransform NewTransform(RandomRotation, Location, Scale);
    return NewTransform;
}


void ASpawner::TrySpawnSpecialEnemy()
{
	if(SpecialEnemyIndex >= SpecialEnemySpawnTime.Num()) return;
	float CurrentTimeSpawn = SpecialEnemySpawnTime[SpecialEnemyIndex];
	if(!SpecialEnemySpawnTime.IsEmpty() && CurrentTimeSpawn <= GameTime)
	{
		SpawnSpecialEnemy();
		SpecialEnemyIndex++;
	}
}

void ASpawner::TrySpawnAsteroid()
{
	if(AsteroidIndex >= AsteroidSpawnTime.Num()) return;
	float CurrentTimeSpawn = AsteroidSpawnTime[AsteroidIndex];
	if(!AsteroidSpawnTime.IsEmpty() && CurrentTimeSpawn <= GameTime)
	{
		int AsteroidLevel = 3;
		FVector SpawnLocation = EnemySpawnLocation + FVector(-700.f, 0, 0);
		AAsteroid* Asteroid = SpawnAsteroid(SpawnLocation, AsteroidLevel);
		AsteroidIndex++;
	}
}