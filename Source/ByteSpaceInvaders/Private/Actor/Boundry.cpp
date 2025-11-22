// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Boundry.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ABoundry::ABoundry()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = BaseSceneComponent;

	BoundryBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoundryBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABoundry::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoundry::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoundry::SetNewBoundry(FVector NewBoundrySize, bool bNewIsHorizontal)
{
	BoundryBox->SetBoxExtent(NewBoundrySize, true);
	bIsHorizontal = bNewIsHorizontal;
}

bool ABoundry::GetIsHorizontal()
{
	return bIsHorizontal;
}