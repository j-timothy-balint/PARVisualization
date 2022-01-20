/**\file ParAIController
\brief The AI controller that connects PAR to the AI systems in Unreal
*/

#pragma once
#include <string>
#include "agentProc.h"
#include "AIController.h"
#include "PARAIController.generated.h"

/**
 * 
 */
UCLASS()
class PAR_VISUALIZER_API APARAIController : public AAIController
{
	GENERATED_BODY()
private:
	AgentProc *par_agent; /*! <A pointer to the par agent class, and what all par information goes through */

public:
		bool initPARAgent(const std::string &name,FVector,FVector,FVector); /*Initalizes the PAR agent */

		AgentProc *getPARAgent(){ return par_agent; } /*! <Returns the PAR agent back to the system*/

		/*These set the PAR movement fields*/
		void setPosition(FVector);
		void setRotation(FVector);
		void cleanPAR(){ delete par_agent; par_agent = NULL; }
		
		/*These two functions are for the IDLE logic*/
		bool isIdle();
		bool runDefaultAction(); //For now, the action is hard-coded
		
};
