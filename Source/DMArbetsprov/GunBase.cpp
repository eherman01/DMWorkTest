// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "CharacterStats.h"
#include "DMArbetsprovProjectile.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	RootComponent = GunMesh;
	GunMesh->bCastDynamicShadow = false;
	GunMesh->CastShadow = false;
	GunMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	//GunMesh->MeshComponentUpdateFlag = 0;
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunBase::Init(UCharacterStats* stats)
{
	characterStats = stats;

	OnFire.AddUObject(this, &AGunBase::LocalFire);

	if (IsNetMode(NM_Client))
		return;

	if (!stats)
	{
		UE_LOG(LogTemp, Error, TEXT("Init failed: CharacterStats not set"));
		return;
	}

	OnFire.AddUObject(this, &AGunBase::Fire);
	OnFire.AddUObject(characterStats, &UCharacterStats::Fire);
	characterStats->GiveAmmo(this, StartingAmmo);
	characterStats->Reload(ClipSize);

}

/** Fire */
void AGunBase::TryFire() 
{
	if (!characterStats) 
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterStats not set. Did you forget to call Init?"));
		return;
	}

	if (characterStats->AmmoInClip > 0) 
	{
		ServerFire();
	}

}

void AGunBase::Fire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FVector position = GunMesh->GetSocketLocation(TEXT("Muzzle"));

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			ADMArbetsprovProjectile* projectile = World->SpawnActor<ADMArbetsprovProjectile>(ProjectileClass, position, AimRot, ActorSpawnParams);

			if(projectile)
				projectile->HitDelegate.BindUObject(this, &AGunBase::OnWeaponHit);
		}
	}

}

void AGunBase::LocalFire() 
{
	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = GunMesh->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AGunBase::ServerFire_Implementation()
{
	if(OnFire.IsBound())
		OnFire.Broadcast();
}

bool AGunBase::ServerFire_Validate()
{
	if (characterStats->AmmoInClip <= 0)
		return false;

	return true;

}

/** On Hit */
void AGunBase::OnWeaponHit(AActor* hit) 
{
	hit->TakeDamage(damage, damageType, Cast<APawn>(GetOwner())->Controller, this);
}

/** Reload */
void AGunBase::Reload()
{
	if (!characterStats)
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterStats not set. Did you forget to call Init?"));
		return;
	}

	if (characterStats->Ammo > 0)
		ServerReload();

}

void AGunBase::ServerReload_Implementation() 
{
	characterStats->Reload(ClipSize);
}

bool AGunBase::ServerReload_Validate()
{
	if (characterStats->Ammo <= 0)
		return false;

	return true;
}

/** Give Ammo */
void AGunBase::GiveAmmo(AActor* ammoSource, int amount)
{
	if (amount <= 0)
		return;

	characterStats->GiveAmmo(ammoSource, amount);

}