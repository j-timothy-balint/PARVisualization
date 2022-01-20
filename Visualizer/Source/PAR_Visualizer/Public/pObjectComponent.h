// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MetaObject.h"
#include "Components/StaticMeshComponent.h"
#include "pObjectComponent.generated.h"

/**
 * A component MetaObject that can keep track of Static Actors
 */
UCLASS(ClassGroup = (PAR), meta = (BlueprintSpawnableComponent))
class PAR_VISUALIZER_API UpObjectComponent : public UStaticMeshComponent
{
	
	GENERATED_BODY()
		UpObjectComponent();

		virtual void BeginPlay() override;

	

private:
	MetaObject *obj;
	
};
