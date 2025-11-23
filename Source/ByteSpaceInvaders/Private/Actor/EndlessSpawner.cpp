// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EndlessSpawner.h"
#include "Actor/EnemyManager.h"

void AEndlessSpawner::StartGame(int Level)
{
    float SpeedModifier = EnemySpeedTimeInfo.GetValueOnLevel(Level, false);
    float SpecialEnemyTime = SpecialEnemyTimeInfo.GetValueOnLevel(Level, true);
    float AsteroidTime = AsteroidTimeInfo.GetValueOnLevel(Level, true);
    float EnemyFireSpeed = EnemyFireSpeedInfo.GetValueOnLevel(Level, false);
    float OrbitalEnemyCount = OrbitalEnemyCountInfo.GetValueOnLevel(Level, false);

    TArray<int> NewEnemyWave;
    int Orbit = 0;
    for(int i=1; i<50; i++)
    {
        SpecialEnemySpawnTime.Add(SpecialEnemyTime*i);
        AsteroidSpawnTime.Add(AsteroidTime*i);
    }

    for(int i=0; i<OrbitalEnemyCount; i++)
    {
        if(NewEnemyWave.Num() <= Orbit) NewEnemyWave.Add(0);
        NewEnemyWave[Orbit]++;
        if(NewEnemyWave[Orbit] > EnemiesOnOrbitMaxCount)
        {
            Orbit++;
        }
    }

    StartWave = FEnemyWave(NewEnemyWave);
    SpawnStartObritalShips(SpeedModifier);
    EnemyManager->SetFireCountBase(EnemyFireSpeed);
    
}   

