// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintFunctions.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EBranchEnum : uint8
{
	SUCCESS,
	FAIL,
};

UCLASS()
class DMARBETSPROV_API UBlueprintFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

};
