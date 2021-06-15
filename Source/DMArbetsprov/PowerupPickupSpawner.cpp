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
	powerup->OnPickupDel.BindUObject(this, &APowerupPickupSpawner::OnPickup);
	
}

ADMArbetsprovGameMode* APowerupPickupSpawner::GetCastedGamemode(EBranchEnum & Branches)
{
	if (IsNetMode(ENetMode::NM_Client))
	{
		Branches = EBranchEnum::FAIL;
		return nullptr;
	}

	ADMArbetsprovGameMode* gm = Cast<ADMArbetsprovGameMode>(GetWorld()->GetAuthGameMode());

	if (!gm)
	{
		Branches = EBranchEnum::FAIL;
		return nullptr;
	}


	Branches = EBranchEnum::SUCCESS;
	return gm;

}

// Called every frame
/*void AItemPickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
