// Fill out your copyright notice in the Description page of Project Settings.
#include "PARAIController.h"
#include "Engine/Engine.h"

extern parTime *partime;
extern Actionary *actionary;

//!Initalizes the PAR component, setting the starting values to be that of the mesh
/*!
	\param name     The agent's (generally unique) name
	\param position The character's starting position
	\param rotation The character's starting rotation
	\param scale    The character's starting scale
	\returns True if the agent is created, and false otherwise
*/
bool 
APARAIController::initPARAgent(const std::string &name, FVector position, FVector rotation, FVector scale){
	try{
		par_agent = new AgentProc(name.c_str()); //std::string(TCHAR_TO_ANSI(*this->GetName())).c_str()
		par_agent->setCapability("ROOT");
		Vector<3> *vec = new Vector < 3 >();
		vec->v[0] = scale.X;
		vec->v[1] = scale.Y;
		vec->v[2] = scale.Z;
		this->par_agent->getObject()->setBoundingPoint(vec, 0);
		vec->v[0] = position.X;
		vec->v[1] = position.Y;
		vec->v[2] = position.Z;
		this->par_agent->getObject()->setPosition(vec);
		vec->v[0] = position.X;
		vec->v[1] = position.Y;
		vec->v[2] = position.Z;
		this->par_agent->getObject()->setOrientation(vec);
	}
	catch (iPARException e){
		return false;
	}
	return true;
}

void APARAIController::setPosition(FVector position){
	Vector<3> *vec = new Vector < 3 >();
	vec->v[0] = position.X;
	vec->v[1] = position.Y;
	vec->v[2] = position.Z;
	this->par_agent->getObject()->setPosition(vec);

}
void APARAIController::setRotation(FVector rotation){
	Vector<3> *vec = new Vector < 3 >();
	vec->v[0] = rotation.X;
	vec->v[1] = rotation.Y;
	vec->v[2] = rotation.Z;
	this->par_agent->getObject()->setOrientation(vec);
}

//!Returns true if the character is idle (it isn't performing an action and has no actions on the iPAR QUEUE
bool 
APARAIController::isIdle(){
	if (par_agent == NULL){
		return true; //It cannot be doing anything if it doesn't have an agent
	}
	if (par_agent->activeAction()) {//Are they currently performing an action
		iPAR *act_exec = this->par_agent->actionExecuting();
		if (act_exec != NULL) {
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow,
			FString::Printf(TEXT("%s"),*FString(act_exec->par->getActionName().c_str())));
	}
		return false;
	}
	if (!par_agent->emptyQueue()){//Are there any actions that it could be doing
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, TEXT("Actions on the Queue!"));
		return false;
	}
	
	return true;
}
//!Creates a default action for the agent to do. Right now it is hardcoded in, but it should come from the database
bool 
APARAIController::runDefaultAction(){
	try{
		iPAR *par = new iPAR("Nod",this->par_agent->getName());
		MetaObject *end = actionary->searchByNameObj("Cup_1");
		par->setObject(end, 0);
		par->setStartTime(partime->getCurrentTime());
		par->setDuration(2);
		par->setFinished(false);
		this->par_agent->addAction(par);
	}
	catch (iPARException e){
		return false;
	}
	return true;
}

