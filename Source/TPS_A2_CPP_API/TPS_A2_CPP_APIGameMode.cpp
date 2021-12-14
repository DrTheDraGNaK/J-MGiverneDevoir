// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPS_A2_CPP_APIGameMode.h"
#include "TPS_A2_CPP_APICharacter.h"
#include "UObject/ConstructorHelpers.h"

ATPS_A2_CPP_APIGameMode::ATPS_A2_CPP_APIGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
