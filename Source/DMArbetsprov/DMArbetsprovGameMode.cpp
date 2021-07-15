// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DMArbetsprovGameMode.h"
#include "DMArbetsprovHUD.h"
#include "DMArbetsprovCharacter.h"
//#include "Math/UnrealMathUtility.h"
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

TSubclassOf<APowerupBase> ADMArbetsprovGameMode::GetRandomPowerup()
{
	if (powerups.Num() <= 0)
		return nullptr;

	int rand = FMath::RandRange(0, powerups.Num() - 1);
	return powerups[rand];

}

/*class ABotPath* ADMArbetsprovGameMode::GetRandomBotPath(Team team)
{
	TArray<class ABotPath*> viable;

	for (auto it = paths.CreateConstIterator(); it; ++it) 
	{
		if (team == Team::Any || team == it->Value)
			viable.Add(it->Key);

	}

	if (viable.Num() <= 0)
		return nullptr;

	int rand = FMath::FRandRange(0, viable.Num());
	return viable[rand];
}
*/