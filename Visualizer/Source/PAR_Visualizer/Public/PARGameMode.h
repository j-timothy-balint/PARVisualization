/**\file PARGameMode
\brief The Main function class for PAR
*/

#pragma once

#include "GameFramework/GameMode.h"
#include "PARGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PAR_VISUALIZER_API APARGameMode : public AGameMode
{
	GENERATED_BODY()
	
	APARGameMode();//Initalizes the game mode. Mostly used to grab references to animation montages

	// Called when the game starts or when spawned
	virtual void PreInitializeComponents() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Called when the game is shutting down
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	int error;

	void loadMontage(const char*, const char*);//Loads all montages from a given file_path, and adds them to a mapping based on the name of the animation
	
	
};
