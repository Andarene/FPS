// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "FPSProject.h"
#include "FPSCharacter.h"
#include "FPSProjectile.h"


AFPSCharacter::AFPSCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	//Create a camera component and attach it to the capsule in the Blueprint
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = CapsuleComponent;

	//Set the camera's location
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);

	//Create and Configure 1st person mesh
	FirstPersonMesh = PCIP.CreateAbstractDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->AttachParent = FirstPersonCameraComponent;
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	

	//Hide the main mesh from the player
	Mesh->SetOwnerNoSee(true);

}

void AFPSCharacter::BeginPlay(){

	Super::BeginPlay();

	if (GEngine){
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("We are using the FPS Player!"));
	}

}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent){
	//Setup gameplay key bindings
	InputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::OnJumpStart);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::OnJumpStop);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::OnFire);

}

void AFPSCharacter::MoveForward(float val){
	if ((Controller != NULL) && (val != 0.0f)){
		//Find out which way is forward
		FRotator rotation = Controller->GetControlRotation();

		//Limit pitch when walking or falling
		if (CharacterMovement->IsMovingOnGround() || CharacterMovement->IsFalling())
		{
			rotation.Pitch = 0.0f;
		}

		//Add movement in the 'forward' direction
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(direction, val);
	}
}

void AFPSCharacter::MoveRight(float val){

	if ((Controller != NULL) && (val != 0.0f)){
		//Find out which way is right
		const FRotator rotation = Controller->GetControlRotation();
		const FVector direction = FRotationMatrix(rotation).GetScaledAxis(EAxis::Y);

		//Add movement in the 'right' direction
		AddMovementInput(direction, val);
	}

}

void AFPSCharacter::OnJumpStart(){ bPressedJump = true; }

void AFPSCharacter::OnJumpStop(){ bPressedJump = false; }

void AFPSCharacter::OnFire(){
	//Try to fire a projectile
	if(ProjectileClass != NULL){
		FVector CameraLoc;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLoc, CameraRot);
		//Muzzle is in camera, convert to world space before offsetting to find final position
		FVector const MuzzleLocation = CameraLoc +  FTransform(CameraRot).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRot;
		MuzzleRotation.Pitch += 10.0f;
		UWorld* const World = GetWorld();
		if(World){
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			//Spawn projectile at Muzzle
			AFPSProjectile* const Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if(Projectile){
				//Use launch direction to fire projectile
				FVector LaunchDir = MuzzleRotation.Vector();
				Projectile->InitVelocity(LaunchDir);
			}
		}
	}
}