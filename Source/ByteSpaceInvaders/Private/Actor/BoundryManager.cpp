// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BoundryManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/TriggerBox.h"
#include "Utility/ByteSpaceInvadersStructures.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "Actor/Boundry.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABoundryManager::ABoundryManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoundryManager::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (!PC) return;

	int32 ViewX, ViewY;
    PC->GetViewportSize(ViewX, ViewY);

	FVector2D ScreenTopLeft(0.f, 0.f);        
    FVector2D ScreenTopRight(ViewX, 0.f);     
    FVector2D ScreenDownLeft(0.f, ViewY);    
    FVector2D ScreenDownRight(ViewX, ViewY);   

    const float PlaneZ = GetActorLocation().Z; 

	FVector WorldDir;
    FVector WorldTopLeft, WorldTopRight, WorldDownLeft, WorldDownRight;

	WorldTopLeft = DeprojectToPlaneZ(ScreenTopLeft, PlaneZ);
	WorldTopRight = DeprojectToPlaneZ(ScreenTopRight, PlaneZ);
	WorldDownLeft = DeprojectToPlaneZ(ScreenDownLeft, PlaneZ);
	WorldDownRight = DeprojectToPlaneZ(ScreenDownRight, PlaneZ);

	PhysicalScreenBoundry.SetPhysicalScreenBoundry(WorldTopLeft, WorldTopRight, WorldDownLeft, WorldDownRight);

	ABoundry* Top = SpawnBoundry(PhysicalScreenBoundry.MiddleTop, true);
	ABoundry* Right = SpawnBoundry(PhysicalScreenBoundry.MiddleRight, false);
	ABoundry* Down = SpawnBoundry(PhysicalScreenBoundry.MiddleDown, true);
	ABoundry* Left = SpawnBoundry(PhysicalScreenBoundry.MiddleLeft, false);
	BoundryBox.SetBoundries(Top, Right, Down, Left);
}

FVector ABoundryManager::DeprojectToPlaneZ(const FVector2D& ScreenPos, float PlaneZ)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (!PC) return FVector();
	FVector WorldOrigin, WorldDir;
	PC->DeprojectScreenPositionToWorld(ScreenPos.X, ScreenPos.Y, WorldOrigin, WorldDir);

	const float T = (PlaneZ - WorldOrigin.Z) / WorldDir.Z;
	return WorldOrigin + WorldDir * T;
}

ABoundry* ABoundryManager::SpawnBoundry(FVector Location, bool bIsHorizontal)
{
	FRotator Rotator = FRotator::ZeroRotator;
    FActorSpawnParameters SpawnParams = FActorSpawnParameters();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; 
    ABoundry* Boundry = GetWorld()->SpawnActor<ABoundry>(BoundryClass, Location, Rotator, SpawnParams);
	check(Boundry);

	FVector NewExtent = bIsHorizontal? 
							FVector(DefaultBoundryWidth, PhysicalScreenBoundry.Length, DefaultBoundryHeight): 
							FVector(PhysicalScreenBoundry.Height, DefaultBoundryWidth, DefaultBoundryHeight);
	Boundry->SetNewBoundry(NewExtent, bIsHorizontal);
	Boundry->OnBoundryDetection.AddDynamic(this, &ABoundryManager::OnBoundryDetection);
	return Boundry;
}

// Called every frame
void ABoundryManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GameTime = UGameplayStatics::GetTimeSeconds(this);

	TArray<AActor*> ActorToRemoveList;
	for (const TPair<AActor* const, float>& Pair : TimeActorCanTravelAgain)
	{
		AActor* Actor = Pair.Key;
		float Time = Pair.Value;
		if(Time<GameTime) ActorToRemoveList.Add(Actor);
	}
	
	for (AActor* Actor : ActorToRemoveList)
	{
		TimeActorCanTravelAgain.Remove(Actor);
	}
}

void ABoundryManager::OnBoundryDetection(ABoundry* Boundry, AActor* DetectedActor)
{
	TArray<AActor*> Keys;
	TimeActorCanTravelAgain.GetKeys(Keys);
	if(Keys.Contains(DetectedActor)) return;

	ABoundry* OppositeBoundry = BoundryBox.GetOppositeBoundry(Boundry);
	bool bIsHorizontal = Boundry->GetIsHorizontal();
	FVector CurrentLocation = DetectedActor->GetActorLocation();
	FVector NewActorLocation = bIsHorizontal? 
									FVector(OppositeBoundry->GetActorLocation().X, CurrentLocation.Y, CurrentLocation.Z):
									FVector(CurrentLocation.X, OppositeBoundry->GetActorLocation().Y, CurrentLocation.Z);
	TimeActorCanTravelAgain.Add(DetectedActor, GameTime+TimeBetweenTravels);
	DetectedActor->SetActorLocation(NewActorLocation);
}

