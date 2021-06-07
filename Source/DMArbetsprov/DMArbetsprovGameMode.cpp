// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DMArbetsprovGameMode.h"
#include "DMArbetsprovHUD.h"
#include "DMArbetsprovCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADMArbetsprovGameMode::ADMArbetsprovGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADMArbetsprovHUD::StaticClass();
}
