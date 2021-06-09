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

	UFUNCTION(BlueprintImplementableEvent, Category = "IngameUI")
	void UpdateHealthbar(float health, float maxHealth);


	//Blueprint helper functions

	UFUNCTION(BlueprintCallable, Category = "IngameUI")
	static void UpdateUITextBlockText(UTextBlock* _textBlock, FString _text);

	UFUNCTION(BlueprintCallable, Category = "IngameUI")
	static void UpdateUIProgressbarProgress(UProgressBar* _progressBar, float _progress);

	UFUNCTION(BlueprintCallable, Category = "Float", meta = (Tooltip = "A is what percent of B?"))
	static float ToPercent(float a, float b);

};
