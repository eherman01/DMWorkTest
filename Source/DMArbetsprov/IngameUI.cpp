// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameUI.h"

UIngameUI::UIngameUI(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UIngameUI::NativeConstruct()
{
	// Do some custom setup

	// Call the Blueprint "Event Construct" node
	Super::NativeConstruct();
}


void UIngameUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// Make sure to call the base class's NativeTick function
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Do your custom tick stuff here
}

////////////////////////////////////////////////////////////////////////
// All of this should definitly be refactored into a static class instead
//
void UIngameUI::UpdateUITextBlockText(UTextBlock* _textBlock, FString _text)
{
	_textBlock->SetText(FText::FromString(_text));
}

void UIngameUI::UpdateUIProgressbarProgress(UProgressBar* _progressBar, float _progress)
{
	_progressBar->SetPercent(_progress);
}

/* a is what percent of b */
float UIngameUI::ToPercent(float a, float b)
{
	return (1.0f / b) * a;
}
