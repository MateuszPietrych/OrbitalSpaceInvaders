// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ByteSpaceInvadersGameMode.h"
#include "Actor/Orbit.h"

void AByteSpaceInvadersGameMode::SetFirstOrbit(AOrbit* NewFirstOrbit)
{
    FirstOrbit = NewFirstOrbit;
}

AOrbit* AByteSpaceInvadersGameMode::GetFirstOrbit()
{
    return FirstOrbit;
}