// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "FPSProject.h"
#include "FPSGameMode.h"


AFPSGameMode::AFPSGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
//	DefaultPawnClass = AFPSCharacter::StaticClass();

	//Set Default Pawn to Blueprint character
	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerPawnObject(TEXT("Blueprint'/Game/Blueprints/BP_FPSCharacter.BP_FPSCharacter'"));
	if (PlayerPawnObject.Object != NULL){ DefaultPawnClass = (UClass*)PlayerPawnObject.Object->GeneratedClass; }
}

void AFPSGameMode::BeginPlay(){
	Super::BeginPlay();

	if (GEngine){
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World"));
	}
}

