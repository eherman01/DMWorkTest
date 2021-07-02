// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintFunctions.h"

float UBlueprintFunctions::ToPercent(float a, float b)
{
	return (1.0f / b) * a;
}