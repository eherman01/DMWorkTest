// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMArbetsprovCharacter.h"
#include "PowerupBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "ItemPickupSpawner.generated.h"

UCLASS()
class DMARBETSPROV_API AItemPickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickupSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

public:

	////////////////////////////////////////////////
	// Components

	UPROPERTY(EditAnywhere)
	USphereComponent* trigger;

	UPROPERTY(EditAnywhere)
	USceneComponent* itemSpawnRoot;

	////////////////////////////////////////////////
	// Vars

	UPROPERTY(BlueprintReadWrite)
	UPowerupBase* currentPowerup;

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "Item Pickup Spawner")
	void OnPickupEmpty();

	UFUNCTION(BlueprintImplementableEvent, Category = "Item Pickup Spawner")
	void OnPickup();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComponent, int32 _otherIndex, bool _bFromSweep, const FHitResult& _sweepResult);

};
