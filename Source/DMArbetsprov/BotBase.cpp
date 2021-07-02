// Fill out your copyright notice in the Description page of Project Settings.


#include "BotBase.h"
#include "DMArbetsprovGameMode.h"
#include "Kismet/GameplayStatics.h"

void ABotBase::GetRandomBotPath(EBranchEnum& Branches)
{
	ADMArbetsprovGameMode* gamemode = Cast<ADMArbetsprovGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!gamemode) 
	{
		Branches = EBranchEnum::FAIL;
		return;
	}

	botPath = gamemode->GetRandomBotPath(team);

	Branches = EBranchEnum::SUCCESS;
	return;
}
