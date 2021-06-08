// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickupSpawner.h"

// Sets default values
AItemPickupSpawner::AItemPickupSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	itemSpawnRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ItemSpawnRoot"));
	itemSpawnRoot->SetupAttachment(RootComponent);

	trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	trigger->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AItemPickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	trigger->OnComponentBeginOverlap.AddDynamic(this, &AItemPickupSpawner::OnOverlapBegin);

}

void AItemPickupSpawner::OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComponent, int32 _otherIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{

	bool isPlayer = _otherActor->IsA(ADMArbetsprovCharacter::StaticClass());
	if (!isPlayer)
		return;

	if (currentPowerup == nullptr) 
	{
		OnPickupEmpty();
		return;
	}

	//Do Local player stuff (handling item pickup etc, done through blueprints)
	OnPickup();

	//Do Server stuff (applying stats etc)
	if (GetNetMode() < NM_Client) 
		currentPowerup->PlayerApplyPowerup(_otherActor);

}

// Called every frame
/*void AItemPickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
