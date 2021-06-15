// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupBase.h"

// Sets default values
APowerupBase::APowerupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	RootComponent = trigger;

}

// Called when the game starts or when spawned
void APowerupBase::BeginPlay()
{
	Super::BeginPlay();
	trigger->OnComponentBeginOverlap.AddDynamic(this, &APowerupBase::OnOverlapBegin);

}

// Called every frame
void APowerupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerupBase::OnOverlapBegin(UPrimitiveComponent* _overlappedComponent, AActor* _otherActor, UPrimitiveComponent* _otherComponent, int32 _otherIndex, bool _bFromSweep, const FHitResult& _sweepResult)
{
	ADMArbetsprovCharacter* player = Cast<ADMArbetsprovCharacter>(_otherActor);

	if (!player)
		return;

	//Do Local player stuff (handling item pickup etc)
	OnPickup();

	//Callback to powerup base
	OnPickupDel.ExecuteIfBound();

	//Do Server stuff (applying stats etc)
	if (GetNetMode() < NM_Client) 
		PlayerApplyPowerup(player);

	//Destroy
	Destroy();
	
}