// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyEnums.h"
#include "BotBase.generated.h"

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
class DMARBETSPROV_API ABotBase : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<Team> team;
	
};
