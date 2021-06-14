// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PowerupBase.h"
#include "DMArbetsprovGameMode.generated.h"

UCLASS(minimalapi)
class ADMArbetsprovGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ADMArbetsprovGameMode();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float powerupSpawnDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float powerupRespawnTime;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APowerupBase>> powerups;

	UFUNCTION(BlueprintCallable)
	TSubclassOf<APowerupBase> GetRandomPowerup();

};



