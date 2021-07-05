// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMArbetsprovGameMode.h"
#include "FFAGamemode.generated.h"

/**
 * 
 */
UCLASS()
class DMARBETSPROV_API AFFAGamemode : public ADMArbetsprovGameMode
{
	GENERATED_BODY()

protected:
	
	virtual void StartPlay();

public:

	//Bad practice, spawn points should be added to gamemode automatically on construction
	//to support gamemode being used in different levels
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bots)
	TArray<TSoftObjectPtr<class APlayerStart>> Spawns;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bots)
	int BotCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bots)
	TSubclassOf<class AAIController> BotController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Bots)
	TSubclassOf<APawn> Bot;

	UFUNCTION(BlueprintCallable)
	APawn* SpawnPawn(TSubclassOf<APawn> toSpawn);

	APawn* SpawnPawn(TSubclassOf<APawn> toSpawn, int AtSpawn);



	
};
