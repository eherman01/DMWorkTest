// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerupBase.h"
#include "DMArbetsprovGameMode.h"
#include "PowerupPickupSpawner.generated.h"

UCLASS()
class DMARBETSPROV_API APowerupPickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerupPickupSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float itemSpawnHeight;

	UFUNCTION(BlueprintCallable, Category = "Powerup Pickup Spawner")
	void SpawnPowerup(TSubclassOf<APowerupBase> _powerup);

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerup Pickup Spawner")
	void OnPickup();

};