// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "FPSProject.h"
#include "FPSProjectile.h"


AFPSProjectile::AFPSProjectile(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//Use a sphere as a simple collision representation
	CollisionComp = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComponent"));
	CollisionComp->InitSphereRadius(15.0f);
	RootComponent = CollisionComp;

	//Use the projectileMovementComponent to govern this projectiles movement

	ProjectileMovement = PCIP.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.3f;

}


void AFPSProjectile::InitVelocity(const FVector &ShootDirection){

	if(ProjectileMovement){
		//Set projectiles velocity to desired direction
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
	}
}

