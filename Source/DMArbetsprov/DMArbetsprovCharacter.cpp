// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DMArbetsprovCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ADMArbetsprovCharacter

ADMArbetsprovCharacter::ADMArbetsprovCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	//Create stat component
	characterStats = CreateDefaultSubobject<UCharacterStats>(TEXT("CharacterStats"));
	characterStats->SetIsReplicated(true);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.
}

void ADMArbetsprovCharacter::Heal(AActor* healingSource, float healingAmount)
{

	if (IsNetMode(NM_Client))
		return;

	if (healingAmount <= 0)
		return;
	
	OnHeal.Broadcast(healingSource, healingAmount);

}

void ADMArbetsprovCharacter::GiveAmmo(AActor* ammoSource, int amount)
{

	if (IsNetMode(NM_Client))
		return;

	if (amount <= 0)
		return;

	UE_LOG(LogTemp, Warning, TEXT("GiveAmmo"));
	characterStats->GiveAmmo(ammoSource, amount);	//Maybe make delegate for consistency / UI integration

}

void ADMArbetsprovCharacter::GiveNewWeapon(TSubclassOf<AGunBase> weapon)
{
	FActorSpawnParameters spawnInfo;
	FTransform spawnTransform = GetActorTransform();

	Gun = GetWorld()->SpawnActor<AGunBase>(weapon, spawnTransform, spawnInfo);
	if (!Gun) 
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn Gun!"));
		return;
	}

	Gun->Init(characterStats);


	if (IsLocallyControlled()) 
	{
		Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}

}

void ADMArbetsprovCharacter::BeginPlay()
{
	// Set up stat delegates
	this->OnTakeAnyDamage.AddDynamic(characterStats, &UCharacterStats::TakeDamage);
	this->OnHeal.AddUObject(characterStats, &UCharacterStats::Heal);

	// Call the base class  
	Super::BeginPlay();

}

//////////////////////////////////////////////////////////////////////////
// Input

void ADMArbetsprovCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire and reload events
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADMArbetsprovCharacter::Fire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ADMArbetsprovCharacter::Reload);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ADMArbetsprovCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADMArbetsprovCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADMArbetsprovCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADMArbetsprovCharacter::LookUpAtRate);
}

void ADMArbetsprovCharacter::Fire()
{
	if (!Gun)
		return;

	Gun->TryFire();

}

void ADMArbetsprovCharacter::Reload()
{
	if (!Gun)
		return;

	Gun->Reload();
}

void ADMArbetsprovCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ADMArbetsprovCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ADMArbetsprovCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADMArbetsprovCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}