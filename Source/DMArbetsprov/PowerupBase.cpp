// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupBase.h"

// Sets default values
APowerupBase::APowerupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));

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
	bool isPlayer = _otherActor->IsA(ADMArbetsprovCharacter::StaticClass());
	if (!isPlayer)
		return;

	//Do Local player stuff (handling item pickup etc, done through blueprints)
	OnPickup();

	//Do Server stuff (applying stats etc)
	if (GetNetMode() < NM_Client)
		PlayerApplyPowerup(_otherActor); //TODO: Fix better way of handling player stats
	
}

