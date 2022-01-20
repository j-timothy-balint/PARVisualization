/**\file SetPArFinished
	\brief A Class that sets a PAR to Finished when Notify is Set.
	In theory, we could create several notifies in this file for different
	effects that we want from Unreal->PAR. 
*/

#pragma once
#include "SetParFinished.generated.h"

UCLASS()
class PAR_VISUALIZER_API USetParFinished : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent*, UAnimSequenceBase*) override;

	
	
};
