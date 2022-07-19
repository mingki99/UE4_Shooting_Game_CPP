// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShootingGame_CPPGameMode.h"
#include "ShootingGame_CPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShootingGame_CPPGameMode::AShootingGame_CPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
