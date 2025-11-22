// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/UtilityBlueprintFunctionLibrary.h"
#include "Game/ByteSpaceInvadersGameMode.h"
#include "Actor/Orbit.h"


AByteSpaceInvadersGameMode* UUtilityBlueprintFunctionLibrary::GetByteSpaceInvadersGameMode(UObject* ContextObject)
{
    if (!ContextObject)
    {
        return nullptr;
    }

    UWorld* World = ContextObject->GetWorld();
    if (!World)
    {
        return nullptr;
    }

    return Cast<AByteSpaceInvadersGameMode>(World->GetAuthGameMode());
}

AOrbit* UUtilityBlueprintFunctionLibrary::GetFirstOrbit(UObject* ContextObject)
{
    AByteSpaceInvadersGameMode* GameMode = GetByteSpaceInvadersGameMode(ContextObject);
    return GameMode->GetFirstOrbit();
}

