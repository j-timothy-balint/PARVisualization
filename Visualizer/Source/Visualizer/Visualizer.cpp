// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Visualizer.h"
#include "Modules/ModuleManager.h"

char *actionLocation;// = "D:/openpar-repo/PAR/actions/";
int PAR::dbg = 1; /*! <Set's the PAR debug file to print out to a file*/
FILE* PAR::file_name = fopen("E:/par.log", "w"); /*! <The file that Par's debug will print out to*/
UWorld* World; /*! <A pointer to the world*/
parTime *partime;
AgentTable agentTable; /*! <A pointer for all the agents used in PAR*/
extern Actionary *actionary;

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Visualizer, "Visualizer" );
