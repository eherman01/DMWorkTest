// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FireDelegate)

UCLASS()
class DMARBETSPROV_API AGunBase : public AActor
{
	GENERATED_BODY()

	FireDelegate OnFire;
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = Ammo)
	int StartingAmmo;

	UPROPERTY(EditAnywhere, Category = Ammo)
	int ClipSize;

	FRotator AimRot;

	UPROPERTY(EditAnywhere, Category = Projectile)
	float damage;

	UPROPERTY(EditAnywhere, Category = Projectile)
	FDamageEvent damageType;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class ADMArbetsprovProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	class UCharacterStats* characterStats;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init(UCharacterStats* stats);

	void TryFire();

	UFUNCTION()
	void Fire();

	void LocalFire();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();

	UFUNCTION()
	void OnWeaponHit(AActor* hit);

	void Reload();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerReload();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void GiveAmmo(AActor * ammoSource, int amount);

};
