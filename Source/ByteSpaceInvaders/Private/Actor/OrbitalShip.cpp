// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/OrbitalShip.h"

// Sets default values
AOrbitalShip::AOrbitalShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOrbitalShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOrbitalShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOrbitalShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

