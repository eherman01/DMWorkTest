// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintFunctions.generated.h"

/**
 * 
 */

UCLASS()
class DMARBETSPROV_API UBlueprintFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/* a is what percent of b */
	UFUNCTION(BlueprintPure, Category = "Math\|Float", meta = (Tooltip = "A is what percent of B?"))
	static float ToPercent(float a, float b);

};
