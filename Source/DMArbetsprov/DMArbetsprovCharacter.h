// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "CharacterStats.h"
#include "GunBase.h"
#include "DMArbetsprovCharacter.generated.h"

class UInputComponent;


DECLARE_MULTICAST_DELEGATE_TwoParams(HealDelegate, AActor*, float)

UCLASS(config=Game)
class ADMArbetsprovCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh1P;

	/** Gun */
	UPROPERTY(ReplicatedUsing = OnGetWeapon, BlueprintReadWrite, VisibleAnywhere, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	class AGunBase* Gun;

	/** First person gun, used by host on listenserver */
	class USkeletalMeshComponent* Gun1PCosmetic;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Widget Class Selector*/
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UIngameUI> WidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCharacterStats* characterStats;

public:
	ADMArbetsprovCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	HealDelegate OnHeal;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(AActor* healingSource, float healingAmount);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void GiveNewWeapon(TSubclassOf<AGunBase> weapon);

	UFUNCTION()
	void OnGetWeapon();

	UFUNCTION()
	void OnTakeDamage(AActor * damagedActor, float damage, const UDamageType * damageType, AController * _instigator, AActor * sourceActor);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnDeath();

	UFUNCTION(BlueprintImplementableEvent, Category = "Death")
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent, Category = "Death")
	void Respawn(AController* _controller);

protected:
	virtual void BeginPlay();

public:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Fires a projectile. */
	void Fire();

	void Reload();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerSyncControlRot(FRotator controlRotation);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastSyncControlRot(FRotator controlRotation);

	UPROPERTY(BlueprintReadWrite)
	FRotator controlRot;
	
protected:

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	bool bIsAlive = true;

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

