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
	GunMesh->SetupAttachment(RootComponent);
	GunMesh->bCastDynamicShadow = false;
	GunMesh->CastShadow = false;

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

void AGunBase::TryFire() 
{
	if (!characterStats) 
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterStats not set. Did you forget to call Init?"));
		return;
	}

	if (characterStats->AmmoInClip > 0)
	{
		if (IsNetMode(NM_Client)) 
		{
			OnFire.Broadcast();			//Fire locally
			ServerFire();
		}

	}	

}

//Fire

void AGunBase::Fire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FTransform spawn = GunMesh->GetSocketTransform(TEXT("Muzzle"));
			const FVector position = spawn.GetLocation() + FVector(10.0f, 0.0f, 0.0f);
			const FRotator rotation = spawn.Rotator();

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<ADMArbetsprovProjectile>(ProjectileClass, position, rotation, ActorSpawnParams);
		}
	}

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
	OnFire.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("ServerFire"));
}

bool AGunBase::ServerFire_Validate()
{
	if (characterStats->AmmoInClip <= 0)
		return false;

	return true;

}

//Reload
void AGunBase::Reload()
{
	if (!characterStats)
	{
		UE_LOG(LogTemp, Error, TEXT("CharacterStats not set. Did you forget to call Init?"));
		return;
	}

	if (characterStats->Ammo > 0)
	{
		characterStats->Reload(ClipSize);
		ServerReload();
		return;
	}

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

//Give Ammo
void AGunBase::GiveAmmo(AActor* ammoSource, int amount)
{
	if (amount <= 0)
		return;

	characterStats->GiveAmmo(ammoSource, amount);
	Client_GiveAmmo(ammoSource, amount);

}

void AGunBase::Client_GiveAmmo_Implementation(AActor* ammoSource, int amount)
{
	if (!IsNetMode(NM_Client))
		return;

	characterStats->GiveAmmo(ammoSource, amount);
	UE_LOG(LogTemp, Warning, TEXT("ClientGiveAmmo"));

}