// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DMArbetsprovGameMode.h"
#include "MyEnums.h"
#include "BotPath.generated.h"

UCLASS()
class DMARBETSPROV_API ABotPath : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ABotPath();

	UPROPERTY(EditAnywhere)
	class USplineComponent* path;

	class ADMArbetsprovGameMode* gamemode;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<OwningTeam> owningTeam = OwningTeam::Any;

	UFUNCTION(BlueprintCallable)
	FVector GetNextPathPoint(UPARAM(Ref) int& currentPoint);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool TryAddToMap();

	virtual void BeginDestroy() override;

};
