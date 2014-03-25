// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "FPSProjectile.generated.h"

/**
 * 
 */
UCLASS()
class AFPSProjectile : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category=Projectile) TSubobjectPtr<USphereComponent> CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement) TSubobjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	void InitVelocity(const FVector &ShootDirection);
	
	
};

