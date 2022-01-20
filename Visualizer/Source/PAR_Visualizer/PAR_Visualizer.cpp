// Fill out your copyright notice in the Description page of Project Settings.

#include "PAR_Visualizer.h"
#include "Humanoid.h"
#include "pObject.h"

parTime *partime;
char *actionLocation;// = "D:/openpar-repo/PAR/actions/";
char *actionary_path;
AgentTable agentTable; //This became a new dependency and the wiki should be updated to reflect that
TArray<AHumanoid*> all_agents; /*! <This is the array that holds all of our PAR agents*/
TMap<int32, ApObject*> all_objects; /*! <A map that maps the object id to the graphical representation of the object*/
TMap<int32, UAnimMontage*> all_montages; /*! <This array holds all of the used montages connected to PAR*/
int PAR::dbg = 1; /*! <Set's the PAR debug file to print out to a file*/
FILE* PAR::file_name = fopen("E:/par.log", "w"); /*! <The file that Par's debug will print out to*/

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, PAR_Visualizer, "PAR_Visualizer" );
