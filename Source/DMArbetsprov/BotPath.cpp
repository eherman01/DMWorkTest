// Fill out your copyright notice in the Description page of Project Settings.


#include "BotPath.h"
#include "Components/SplineComponent.h"

//TArray<ABotPath*> ABotPath::paths;

ABotPath::ABotPath()
{
	path = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	path->AttachTo(RootComponent);

}

FVector ABotPath::GetNextPathPoint(UPARAM(Ref) int& currentPoint)
{
	FVector point = path->GetLocationAtSplinePoint(currentPoint, ESplineCoordinateSpace::World);
	currentPoint += 1;

	return point;
}

// Called when the game starts or when spawned
void ABotPath::BeginPlay()
{
	Super::BeginPlay();

	if (!TryAddToMap()) 
	{
		Destroy(this);
		return;
	}

}

/* Tries to add path to map of all paths. Fails if cast fails or if client */
bool ABotPath::TryAddToMap()
{
	if (IsNetMode(ENetMode::NM_Client))
		return false;

	gamemode = Cast<ADMArbetsprovGameMode>(GetWorld()->GetAuthGameMode());

	if (!gamemode)
		return false;

	gamemode->paths.Add(this, owningTeam);
	return true;
}

void ABotPath::BeginDestroy()
{
	Super::BeginDestroy();

	if (gamemode)
	{
		gamemode->paths.Remove(this);
	}
}
