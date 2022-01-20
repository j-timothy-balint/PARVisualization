// Fill out your copyright notice in the Description page of Project Settings.

#include "PARGameMode.h"
#include "lwnet.h"
#include "ParFunctions.h"
#include "Humanoid.h"
#include "pObject.h"
#include "partable.h"
#include <fstream>
#include <string>
#include <sstream>



//extern TArray<AHumanoid*> all_agents;
extern TMap<int32,UAnimMontage*> all_montages;
extern char *actionLocation;
extern char *actionary_path;

extern AgentTable agentTable; //This became a new dependency and the wiki should be updated to reflect that
extern TArray<AHumanoid*> all_agents; /*! <This is the array that holds all of our PAR agents*/
extern TMap<int32, ApObject*> all_objects; /*! <A map that maps the object id to the graphical representation of the object*/


APARGameMode::APARGameMode(){
	error = 0;
	std::string path = __FILE__; //gets the current cpp file's path with the cpp file
	path = path.substr(0, 1 + path.find_last_of('\\')); //removes filename
	//Here, we make the action location relative
	actionLocation = new char[128];
	sprintf_s(actionLocation,128,"%s%s",path.c_str(), "..\\..\\..\\..\\..\\PAR\\actions\\");
	//and here, we make the montage location relative
	actionary_path = new char[256];
	sprintf_s(actionary_path,256,"%s%s",path.c_str(),"..\\..\\..\\Content\\");
	char montage_locations[128];
	char file_name[256];
	sprintf_s(montage_locations, 128, "%s","AnimMontage'/Game/Animations/");
	sprintf_s(file_name, 256, "%s%s", path.c_str(), "..\\..\\..\\Content\\Animations\\animations.txt");
	this->loadMontage(file_name, montage_locations);
}
// Called when the game starts or when spawned
void
APARGameMode::PreInitializeComponents(){
	Super::PreInitializeComponents();	
	setupActionTable();
}

// Called every frame
void
APARGameMode::Tick(float DeltaSeconds){
	Super::Tick(DeltaSeconds);
	//partime->setTimeOffset(partime->getCurrentTime() + DeltaSeconds);
	int par_error = 0;
	LWNetList::advance(&par_error);
}

//Called during the very end
void
APARGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	for (AHumanoid* actor : all_agents) {
		agentTable.removeAgent(TCHAR_TO_UTF8(*(actor->GetName())));
	}
	all_agents.Empty();
	all_objects.Empty();

}

///////////////////////////////////////////////////////////////////////////////
//This function loads in all montages that are written into a text file. We do
//this to help us know what we called the montages
void
APARGameMode::loadMontage(const char* file_name, const char* montage_name){
	std::fstream actions;
	std::stringstream anim_location;
	actions.open(file_name,std::fstream::in);//
	std::string line;
	
	if (actions.is_open()){
		while (getline(actions, line)){
			std::size_t hyphon = line.find("-");
			if (hyphon != std::string::npos){
				anim_location << montage_name << line.substr(hyphon+1) << "\'";
				static ConstructorHelpers::FObjectFinder<UAnimMontage> TestMontage(ANSI_TO_TCHAR(anim_location.str().c_str()));
				all_montages.Add(std::stoi(line.substr(0,hyphon)),TestMontage.Object);
				anim_location.clear();
				anim_location.str(std::string());
			}
		}
		actions.close();
	}

}


