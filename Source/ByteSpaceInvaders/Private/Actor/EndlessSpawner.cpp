// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EndlessSpawner.h"
#include "Actor/EnemyManager.h"

void AEndlessSpawner::StartGame(int Level)
{
    float SpeedModifier = EnemySpeedTimeInfo.GetValueOnLevel(Level, false);
    float SpecialEnemyTime = SpecialEnemyTimeInfo.GetValueOnLevel(Level, true);
    float AsteroidTime = AsteroidTimeInfo.GetValueOnLevel(Level, true);
    float EnemyFireSpeed = EnemyFireSpeedInfo.GetValueOnLevel(Level, false);

    for(int i=1; i<50; i++)
    {
        SpecialEnemySpawnTime.Add(SpecialEnemyTime*i);
        AsteroidSpawnTime.Add(AsteroidTime*i);
    }
    SpawnStartObritalShips(SpeedModifier);
    EnemyManager->SetFireCountBase(EnemyFireSpeed);
}   

