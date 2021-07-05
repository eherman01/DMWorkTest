// Fill out your copyright notice in the Description page of Project Settings.


#include "FFAGamemode.h"
#include "BotBase.h"
#include "GameFramework/PlayerStart.h"

void AFFAGamemode::StartPlay() 
{
	Super::StartPlay();

	if (Spawns.Num() <= 0)
		return;

	for (int i = 0; i < BotCount; i++)
	{
		FActorSpawnParameters spawnInfo;
		ABotBase* botController = GetWorld()->SpawnActor<ABotBase>(BotController, FVector::ZeroVector, FRotator::ZeroRotator, spawnInfo);
		APawn* botPawn = SpawnPawn(Bot);
		botController->Possess(botPawn);

	}

}

APawn* AFFAGamemode::SpawnPawn(TSubclassOf<APawn> toSpawn)
{
	return SpawnPawn(toSpawn, -1);
}

APawn* AFFAGamemode::SpawnPawn(TSubclassOf<APawn> toSpawn, int AtSpawn)
{
	int index;
	if (AtSpawn < 0)
		index = FMath::RandRange(0, Spawns.Num() - 1);
	else
		index = AtSpawn;

	TSoftObjectPtr<APlayerStart> spawn = Spawns[index];

	//Spawn bot
	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	FVector spawnPos = spawn->GetActorLocation();
	FRotator spawnRot = spawn->GetActorRotation();

	APawn* spawnedPawn = GetWorld()->SpawnActor<APawn>(toSpawn, spawnPos, spawnRot, spawnInfo);

	if (spawnedPawn == nullptr)
	{
		return SpawnPawn(toSpawn, (index + 1) % Spawns.Num());
	}

	return spawnedPawn;

}