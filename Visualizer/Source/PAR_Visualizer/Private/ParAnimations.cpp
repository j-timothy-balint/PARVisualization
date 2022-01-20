// Fill out your copyright notice in the Description page of Project Settings.

#include "ParAnimations.h"
#include "agentProc.h"
#include "metaobject.h"

UParAnimations::UParAnimations(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//set any default values for your variables here
	agent = NULL;
	state_switch = 0;
	speed = 0.0f;
	ik_alpha = 0.0f;
	direction = 0.0f;
	use_left_hand = false;
}
/*The getter and setter for AgentProc*/
void UParAnimations::setAgent(AHumanoid* in_agent){
	this->agent = in_agent;
}
AHumanoid* UParAnimations::getAgent(){
	return  agent;
}

void UParAnimations::moveCharacter(){
	/*Here we calculate the velocity by the speed, direction, and foward vector*/
	APawn *pawn =this->TryGetPawnOwner();
	if (pawn != NULL){
		FRotator rot=pawn->GetActorRotation();
		FVector vel=pawn->GetVelocity();//Needs to be length
		direction = this->CalculateDirection(vel, rot);
		speed = vel.Size();
		par_debug("speed is %f and direction is %f\n", speed, direction);
	}
}

void UParAnimations::update(float delta){
	if (state_switch == 2){ //Walking
		this->moveCharacter();
	}
}
