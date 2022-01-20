#include "ParFunctions.h"
#include "agentProc.h"
#include "metaobject.h"
#include "Humanoid.h"
#include "pObject.h"
#include "PARAIController.h"
#include "ParAnimations.h"
#include "utility.h"


extern ActionTable actionTable; //Holds the mapping of actions to real world code
extern TArray<AHumanoid*> all_agents;
extern TMap<int32, ApObject*> all_objects;
extern TMap<int32, UAnimMontage*> all_montages;
extern Actionary *actionary;
extern parTime *partime;
extern PythonTable pytable;


AHumanoid *getAgent(MetaObject *agent){
	if (agent == NULL)
		return NULL;
	AHumanoid *hum = NULL;
	for (auto& ag : all_agents){
		if (agent == ag->getAIAgent()->getPARAgent()->getObject()){
			hum = ag;
		}
	}
	return hum;
}

AHumanoid *getAgent(const std::string &name){
	FString test_name(name.c_str());
	AHumanoid *hum = NULL;
	for (auto& ag : all_agents){
		if (test_name == ag->GetName()){
			hum = ag;
		}
	}
	return hum;

}

ApObject* getObject(MetaObject *obj){
	if (obj == NULL){
		return NULL;
	}
	if (all_objects.Contains(obj->getID())){
		return all_objects[obj->getID()];
	}
	return NULL;
}

ApObject* getObject(const std::string name){
	ApObject *obj = NULL;
	FString test_name(name.c_str());
	for (auto it = all_objects.CreateConstIterator(); it; ++it){
		if (it.Value()->GetName() == test_name){
			obj = it.Value();
		}
	}
	return obj;
}

//!Mapped Action runs a pre-canned animation or controller montage on top of other animations
/*!
\param ipar The Instanced PAR being realized
*/
int doMappedAction(iPAR *ipar){
	MetaObject * agent = ipar->getAgent();
	AHumanoid *hum = getAgent(agent);
	if (hum != NULL){
		hum->AddAction(all_montages[ipar->par->getID()]);//We map actions to their ID
	}
	return 1;
}
//!Mapped Action to perform a walking action between an agent and an object (or a point, but that isn't finished)
/*!
\param ipar The Instanced PAR being realized
*/
int doWalk(iPAR *ipar){
	//Get the agent (for all actions)
	MetaObject *agent = ipar->getAgent();
	AHumanoid *hum = getAgent(agent);
	if (hum != NULL){
		//Set the speed and direction of the object
		UParAnimations* anim = Cast<UParAnimations>(hum->GetMesh()->GetAnimInstance());//This converts the animation blueprint into a class for us
		if (anim != NULL){
			anim->state_switch = 2;
			anim->speed = 50.0f;//1 m/s
		}
		//Get the object to walk to
		MetaObject *walk_obj = ipar->getObject(0);
		if (walk_obj->isAgent()){//Use a different function if the actor is an agent
			AHumanoid *obj = getAgent(walk_obj);
			hum->getAIAgent()->MoveToActor(obj);
		}
		else{
			ApObject * obj = getObject(walk_obj);
			hum->getAIAgent()->MoveToLocation(obj->GetActorLocation(),obj->getPARObject()->getBoundingRadius()*100);// , 1.0, true, true, true, false);
		}
		return 1;
	}
	return 2;
}

//!Mapped Action to perform a reaching action between an agent and an object (or a point, but that isn't finished)
/*!
\param ipar The Instanced PAR being realized
*/
int doReach(iPAR *ipar){
	MetaObject *agent = ipar->getAgent();
	AHumanoid *hum = getAgent(agent);
	if (hum != NULL){
		MetaObject *reach_obj = ipar->getObject(0);
		ApObject * obj = getObject(reach_obj);
		UParAnimations* anim = Cast<UParAnimations>(hum->GetMesh()->GetAnimInstance());//This converts the animation blueprint into a class for us
		if (anim != NULL && obj != NULL){
			anim->state_switch = 11;
			anim->end_effector = FTransform(obj->GetActorLocation());
			anim->ik_alpha = 1.0f;
			return 1;
		}
	}
	return 2;

}

int setState(int agent_id, void* state){
	int state_to_change = *((int *)state);
	MetaObject *agent = actionary->searchByIdObj(agent_id);
	AHumanoid *hum = getAgent(agent);
	if (hum != NULL){
		hum->getAnimationBlueprint()->state_switch = state_to_change;
		return 1;
	}
	return 2;
}

int getState(int agent_id, void*){
	MetaObject *agent = actionary->searchByIdObj(agent_id);
	AHumanoid *hum = getAgent(agent);
	if (hum != NULL){
		return hum->getAnimationBlueprint()->state_switch;
	}
	return -1;

}

void setupActionTable(){
	partime = new parTime();
	partime->setTimeOffset(0);
	partime->setTimeRate(1);			// how fast should time change
	actionary = new Actionary();
	actionary->init();
	//Finally, we add all of our actions to the action table
	actionTable.addFunctions("Nod", &doMappedAction);
	actionTable.addFunctions("Walk", &doWalk);
	actionTable.addFunctions("Get", &doReach);

	pytable.addFunctions("setState", &setState);
	pytable.addFunctions("getState", &getState);
}