// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utility/ByteSpaceInvadersStructures.h"
#include "BoundryManager.generated.h"

class ABoundry;

USTRUCT(BlueprintType)
struct FBoundryBox
{
	GENERATED_BODY()

public:
	void SetBoundries(ABoundry* Top, ABoundry* Right, ABoundry* Down, ABoundry* Left)
	{
		Boundries.Add(Top);
		Boundries.Add(Right);
		Boundries.Add(Down);
		Boundries.Add(Left);
	}

	ABoundry* GetOppositeBoundry(ABoundry* Boundry)
	{
		if(Boundries.Contains(Boundry))
		{
			int Index = Boundries.Find(Boundry);
			int OppositeBoundryIndex = (Index+2)%Boundries.Num();
			return Boundries[OppositeBoundryIndex];
		}
		return Boundry;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ABoundry*> Boundries;
};

UCLASS()
class BYTESPACEINVADERS_API ABoundryManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoundryManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	FVector DeprojectToPlaneZ(const FVector2D& ScreenPos, float PlaneZ);
	
	UFUNCTION()
	void OnBoundryDetection(ABoundry* Boundry, AActor* DetectedActor);

	UPROPERTY()
	FPhysicalScreenBoundry PhysicalScreenBoundry;

private:
	ABoundry* SpawnBoundry(FVector Location, bool bIsHorizontal);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BoundryData, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABoundry> BoundryClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BoundryData, meta = (AllowPrivateAccess = "true"))
	float DefaultBoundryWidth = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BoundryData, meta = (AllowPrivateAccess = "true"))
	float DefaultBoundryHeight = 1500.f;

	UPROPERTY()
	TMap<AActor*, float> TimeActorCanTravelAgain;

	UPROPERTY()
	FBoundryBox BoundryBox;

	float GameTime = 0.0f;

	float TimeBetweenTravels = 5.0f;



};
