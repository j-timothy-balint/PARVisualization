// Fill out your copyright notice in the Description page of Project Settings.


#include "ParSetup.h"
#include "lwnet.h"
#include "Visualizer.h"
#include <fstream>
#include <sstream>
//#include "ParFunctions.h"



//extern TArray<AHumanoid*> all_agents;
extern Actionary *actionary;
extern parTime *partime;
extern char *actionLocation;
extern UWorld* World;

void setupActionTable(); //A function that will hold all the actions that a character can do. This may move, but for now this is the best place for it.

AParSetup::AParSetup() {
	error = 0;
	std::string path = __FILE__; //gets the current cpp file's path with the cpp file
	path = path.substr(0, 1 + path.find_last_of('\\')); //removes filename
	//Here, we make the action location relative
	actionLocation = new char[128];
	sprintf_s(actionLocation, 128, "%s%s", path.c_str(), "..\\..\\..\\..\\PAR\\actions\\");

	/*This will initalize the animations when we start to have animations*/
	/*char montage_locations[128];
	char file_name[128];
	sprintf_s(montage_locations, 128, "%s", "AnimMontage'/Game/Animations/");
	sprintf_s(file_name, 128, "%s%s", path.c_str(), "..\\..\\..\\Content\\Animations\\animations.txt");
	this->loadMontage(file_name, montage_locations);
	*/
}
// Called when the game starts or when spawned
void
AParSetup::PreInitializeComponents() {
	Super::PreInitializeComponents();
	setupActionTable();
	World = GetWorld();
	//this->addParObjects();

	//this->setVisibility();
}

// Called every frame
void
AParSetup::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	//partime->setTimeOffset(partime->getCurrentTime() + DeltaSeconds);
	error = 0;
	LWNetList::advance(&error);
}

void setupActionTable() {
	partime = new parTime();
	partime->setTimeOffset(0);
	partime->setTimeRate(1);			// how fast should time change
	actionary = new Actionary();
	actionary->init();
	//Finally, we add all of our actions to the action table
	//actionTable.addFunctions("Nod", &doMappedAction);
	//actionTable.addFunctions("Walk", &doWalk);
	//actionTable.addFunctions("Pull", &doReach);

	//pytable.addFunctions("setState", &setState);
	//pytable.addFunctions("getState", &getState);

}