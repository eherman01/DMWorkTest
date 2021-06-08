// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PowerupBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DMARBETSPROV_API UPowerupBase : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FString name;

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerup", meta = (ToolTip = "Should only ever run on server"))
	void PlayerApplyPowerup(AActor* _player);
	
};
