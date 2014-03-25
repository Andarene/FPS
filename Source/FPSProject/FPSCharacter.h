// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AFPSCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	virtual void BeginPlay() OVERRIDE;
	protected:
		virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE;
		UFUNCTION() void MoveForward(float val); // Moves player forward and backward
		UFUNCTION() void MoveRight(float val); // Moves player left and right
		UFUNCTION() void OnJumpStart(); // sets jump flag when key is pressed
		UFUNCTION() void OnJumpStop(); //Clears jump flag when key is released
		UFUNCTION() void OnFire(); // Fires a projectile

		/*** First Person Camera **/
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera) TSubobjectPtr<UCameraComponent> FirstPersonCameraComponent;

		/*** Pawn Mesh: 1st Person view (arms; only seen by self)***/
		UPROPERTY(VisibleDefaultsOnly, Category=Mesh) TSubobjectPtr<USkeletalMeshComponent> FirstPersonMesh;

		//Gun Muzzles offset from cameras location
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) FVector MuzzleOffset;

		//Projectile class to spawn
		UPROPERTY(EditDefaultsOnly, Category=Projectile)TSubclassOf<class AFPSProjectile> ProjectileClass;


};
