// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerupBase.h"
#include "DMArbetsprovGameMode.h"
#include "PowerupPickupSpawner.generated.h"

UENUM(BlueprintType)
enum class EBranchEnum : uint8
{
	SUCCESS,
	FAIL,
};

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

	UFUNCTION(BlueprintCallable, Category = "Powerup Pickup Spawner", Meta = (ExpandEnumAsExecs = "Branches",
		ToolTip = "Will fail if netmode is client or if gamemode cannot be cast to DMArbetsprovGameMode."))
	ADMArbetsprovGameMode* GetCastedGamemode(EBranchEnum& Branches);

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerup Pickup Spawner")
	void OnPickup();

};