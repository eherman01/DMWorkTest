// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupPickupSpawner.h"

// Sets default values
APowerupPickupSpawner::APowerupPickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APowerupPickupSpawner::BeginPlay()
{
	Super::BeginPlay();

}

void APowerupPickupSpawner::SpawnPowerup(TSubclassOf<APowerupBase> _powerup)
{
	if (_powerup == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("No actor to spawn assigned!"))
		return;
	}

	FActorSpawnParameters spawnInfo;
	FVector spawnPos = FVector::UpVector * itemSpawnHeight;
	FRotator spawnRot = FRotator::ZeroRotator;

	APowerupBase* powerup = GetWorld()->SpawnActor<APowerupBase>(_powerup, spawnPos, spawnRot, spawnInfo);
	powerup->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called every frame
/*void AItemPickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
