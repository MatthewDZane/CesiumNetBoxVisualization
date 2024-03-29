// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetBoxVisualization.generated.h"

UCLASS(Abstract, Blueprintable)
class CESIUMNETBOXVISUALIZATION_API ANetBoxVisualization : public AActor
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UI")
		void HideDisplays();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, BlueprintPure, Category="Utility")
		FRotator GetRotationRelativeToSurface(FVector Location);

};
