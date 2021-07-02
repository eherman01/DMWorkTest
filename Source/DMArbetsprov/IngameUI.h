// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "IngameUI.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DMARBETSPROV_API UIngameUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UIngameUI(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadonly)
	class UCharacterStats* characterStats;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI Events")
	void UpdateMaxHealth(float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI Events")
	void UpdateHealth(float Health);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI Events")
	void UpdateAmmoInClip(int AmmoInClip);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI Events")
	void UpdateAmmo(int Ammo);

};
