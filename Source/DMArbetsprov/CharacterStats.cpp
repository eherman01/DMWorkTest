// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStats.h"

// Sets default values for this component's properties
UCharacterStats::UCharacterStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Owner = GetOwner();

	bReplicates = true;

	MaxHealth = 100.0f;
	Health = MaxHealth;

}


// Called when the game starts
void UCharacterStats::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UCharacterStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCharacterStats::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UCharacterStats, MaxHealth);
	DOREPLIFETIME(UCharacterStats, Health);

}

void UCharacterStats::TakeDamage(AActor * damagedActor, float damage, const UDamageType * damageType, AController * instigator, AActor * sourceActor)
{
	if (damage <= 0)
		return;

	Health = FMath::Max(Health - damage, 0.0f);

}

void UCharacterStats::Heal(AActor* healingSource, float healAmount)
{
	if (healAmount <= 0)
		return;

	Health = FMath::Min(Health + healAmount, MaxHealth);

}