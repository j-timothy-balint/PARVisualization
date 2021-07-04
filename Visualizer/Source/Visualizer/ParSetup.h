// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetData.h"
#include "GameFramework/GameModeBase.h"
#include "ParSetup.generated.h"

/**
 * 
 */
UCLASS()
class VISUALIZER_API AParSetup : public AGameModeBase
{
	GENERATED_BODY()
	
		AParSetup();//Initalizes the game mode. Mostly used to grab references to animation montages

		// Called when the game starts or when spawned
	virtual void PreInitializeComponents() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


private:
	int error;
	TMap<FString, FAssetData> names;

};
