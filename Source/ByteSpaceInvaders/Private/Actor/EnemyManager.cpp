// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EnemyManager.h"
#include "Actor/OrbitalShip.h"
#include "TimerManager.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ChangeDirectionTimer, this, &AEnemyManager::ChangeMovementDirection, TimeUntilChangeDirection, true);
	GetWorld()->GetTimerManager().SetTimer(LowerOrbitTimer, this, &AEnemyManager::LowerOrbit, TimeOnSingleOrbit, true);

	float FinalPeriodBetweenFires = GetTimePeriodBetweenFires();
	GetWorld()->GetTimerManager().SetTimer(FiresTimer, this, &AEnemyManager::Fire, FinalPeriodBetweenFires, false);
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyManager::FinishSpawningEnemies(TArray<AOrbitalShip*> SpawnedShipList)
{
	OrbitalShips = SpawnedShipList;
	for(AOrbitalShip* Ship: OrbitalShips)
	{
		Ship->OnShipDeath.AddDynamic(this, &AEnemyManager::RemoveShipFromList);
	}

}

void AEnemyManager::SetFireCountBase(int FireCount)
{
	FireCountBase = FireCount;
}

void AEnemyManager::LowerOrbit()
{
	for(AOrbitalShip* Ship: OrbitalShips)
	{
		if(SpecialShips.Contains(Ship)) return;
		Ship->LowerOrbit();
	}
}

void AEnemyManager::ChangeMovementDirection()
{
	for(AOrbitalShip* Ship: OrbitalShips)
	{
		if(SpecialShips.Contains(Ship)) return;
		Ship->ChangeDirection();
	}
}

void AEnemyManager::Fire()
{
	int FinalFireCount = GetFireCount();
	
	for(int Index : GetRandomEnemyIndexes(FinalFireCount))
	{
		if(OrbitalShips.IsValidIndex(Index) && OrbitalShips[Index] != nullptr)
		{
			OrbitalShips[Index]->FireProjectile();
		}
	}

	float FinalPeriodBetweenFires = GetTimePeriodBetweenFires();
	GetWorld()->GetTimerManager().SetTimer(FiresTimer, this, &AEnemyManager::Fire, FinalPeriodBetweenFires, false);
}

float AEnemyManager::GetTimePeriodBetweenFires()
{
	float RandomChangeToPeriod = FMath::FRandRange(-MaxRandomChangeToPeroid, MaxRandomChangeToPeroid);
	float FinalPeroidBetweenFires = PeroidBetweenFiresBase + RandomChangeToPeriod;
	return FinalPeroidBetweenFires;
}

int AEnemyManager::GetFireCount()
{
	int RandomChangeToFireCount = FMath::RandRange(-MaxRandomFireCountChange, MaxRandomFireCountChange); 
	int FinalFireCount = FireCountBase + RandomChangeToFireCount;
	return FinalFireCount;
}

TArray<int> AEnemyManager::GetRandomEnemyIndexes(int EnemyCount)
{
	TArray<int> IndexList = TArray<int>();
	int LastIndex = OrbitalShips.Num()-1;
	if(EnemyCount >= LastIndex) 
	{
		for (int32 i = 0; i <= LastIndex; i++) IndexList.Add(i);
		return IndexList;
	}
	
	for (int32 i = 0; i <= EnemyCount; i++) 
	{
		int RandomChangeToFireCount = FMath::RandRange(0, LastIndex);
		if(IndexList.Contains(RandomChangeToFireCount)) continue;
		IndexList.Add(RandomChangeToFireCount);
	}
	return IndexList;
}

void AEnemyManager::AddEnemy(AOrbitalShip* Ship)
{
	Ship->OnShipDeath.AddDynamic(this, &AEnemyManager::RemoveShipFromList);
	OrbitalShips.Add(Ship);
	SpecialShips.Add(Ship);
}

void AEnemyManager::RemoveShipFromList(AOrbitalShip* Ship)
{
	if(OrbitalShips.Contains(Ship))
	{
		OrbitalShips.Remove(Ship);
		if(OrbitalShips.IsEmpty()) OnDestroyingLastEnemy.Broadcast();
	}
}

void AEnemyManager::Reset_Implementation()
{
	for(AOrbitalShip* Ship: OrbitalShips)
	{
		RemoveShipFromList(Ship);
		Ship->Destroy();
	}
}