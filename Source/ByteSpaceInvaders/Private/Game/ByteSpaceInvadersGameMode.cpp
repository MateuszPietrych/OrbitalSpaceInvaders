// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ByteSpaceInvadersGameMode.h"
#include "Actor/Orbit.h"
#include "Actor/Spawner.h"
#include "Kismet/GameplayStatics.h"
#include "Interface/Resetable.h"

void AByteSpaceInvadersGameMode::SetFirstOrbit(AOrbit* NewFirstOrbit)
{
    FirstOrbit = NewFirstOrbit;
}

AOrbit* AByteSpaceInvadersGameMode::GetFirstOrbit()
{
    return FirstOrbit;
}

void AByteSpaceInvadersGameMode::InitalizeSpawner()
{
    AActor* Actor = UGameplayStatics::GetActorOfClass(GetWorld(), SpawnerClass);
    ASpawner* Spawner = Cast<ASpawner>(Actor);
    if(Spawner)
    {
        Spawner->StartGame(Level);
    }
}

void AByteSpaceInvadersGameMode::ResetGame()
{
    TArray<AActor*> Actors;
    UGameplayStatics::GetAllActorsWithInterface(
        GetWorld(),
        UResetable::StaticClass(), 
        Actors
    );

    for (AActor* Actor : Actors)
    {
        if (!Actor) continue;

        if (Actor->GetClass()->ImplementsInterface(UResetable::StaticClass()))
        {
            IResetable::Execute_Reset(Actor);
        }
    }
    GameReset.Broadcast();
}