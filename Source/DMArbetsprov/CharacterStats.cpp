// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStats.h"
#include "IngameUI.h"

// Sets default values for this component's properties
UCharacterStats::UCharacterStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

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
	
	DOREPLIFETIME_CONDITION(UCharacterStats, MaxHealth, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UCharacterStats, Health, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UCharacterStats, Ammo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UCharacterStats, AmmoInClip, COND_OwnerOnly);

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

void UCharacterStats::GiveAmmo(AActor* ammoSource, int amount)
{
	if (amount <= 0)
		return;

	Ammo += amount;

}

void UCharacterStats::Fire()
{
	if (AmmoInClip < 1)
		return;

	AmmoInClip -= 1;
}

void UCharacterStats::Reload(int clipSize)
{
	if (clipSize < 1)
		return;

	int ammoToLoad = FMath::Min(clipSize - AmmoInClip, Ammo);
	AmmoInClip += ammoToLoad;
	Ammo -= ammoToLoad;

}