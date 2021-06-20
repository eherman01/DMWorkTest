// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"
#include "CharacterStats.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DMARBETSPROV_API UCharacterStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStats();

	AActor* Owner;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(replicated, EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(replicated, EditAnywhere, BlueprintReadOnly, Category = "Health")
	float Health;

	UPROPERTY(replicated, EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int Ammo;

	UPROPERTY(replicated, EditAnywhere, BlueprintReadOnly, Category = "Ammo")
	int AmmoInClip;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;

	UFUNCTION()
	void TakeDamage(AActor* damagedActor, float damage, const UDamageType* damageType, class AController* instigator, AActor* sourceActor);

	UFUNCTION()
	void Heal(AActor* healingSource, float healAmount);

	UFUNCTION()
	void GiveAmmo(AActor * ammoSource, int amount);

	UFUNCTION()
	void Fire();

	void Reload(int clipSize);

};
