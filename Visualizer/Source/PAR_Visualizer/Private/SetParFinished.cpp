// Fill out your copyright notice in the Description page of Project Settings.
#include "SetParFinished.h"

#include "Humanoid.h"
#include "ParAnimations.h"
#include "PARAIController.h"

void
USetParFinished::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	UParAnimations* anim = Cast<UParAnimations>(MeshComp->GetAnimInstance());//This converts the animation blueprint into a class for us
	if (anim != NULL){
		AHumanoid *agent = anim->getAgent();
		if (agent != NULL){
			//At this point, we want to set the currently executing iPAR to NULL
			iPAR *par = agent->getAIAgent()->getPARAgent()->actionExecuting();
			if (par != NULL){
				par_debug("Action is %s that we are finishing...\n", par->par->getActionName().c_str());
				par->setFinished(true);
			}
			
		}
	}
}