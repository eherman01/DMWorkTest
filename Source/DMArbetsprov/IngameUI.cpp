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