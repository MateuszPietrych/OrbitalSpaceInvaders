// Fill out your copyright notice in the Description page of Project Settings.



#include "Component/WeaponComponent.h"
#include "Actor/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"


void UWeaponComponent::SpawnProjectile(TSubclassOf<AProjectile> ProjectileClass, float Damage)
{
	FTransform SocketTransform;
	if (DoesSocketExist(ProjetileSocketName))
	{
		SocketTransform = GetSocketTransform(ProjetileSocketName, ERelativeTransformSpace::RTS_World);
	}
	else
	{
		SocketTransform = GetComponentTransform();
	}

	FRotator Rotation = SocketTransform.GetRotation().Rotator();
	FVector Location = SocketTransform.GetLocation();
	AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	if(!SpawnedProjectile) return;
	SpawnedProjectile->InitializeProjectile(Damage);
}

