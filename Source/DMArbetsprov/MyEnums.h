// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyEnums.generated.h"

/**
 * 
 */
UCLASS()
class DMARBETSPROV_API UMyEnums : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


};

UENUM()
enum OwningTeam {
	Any,
	TeamA,
	TeamB,
};
