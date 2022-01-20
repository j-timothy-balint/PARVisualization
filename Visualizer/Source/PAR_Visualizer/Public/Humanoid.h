/** \file Humanoid.h
	\brief The Base Agent Human Class -> AHumanoid
	The Humanoid class provides a base for all PAR characters. It connects the AI
	system to the animation system, as well as the mesh
*/

#pragma once

#include "GameFramework/Character.h"
#include "Humanoid.generated.h"


class APARAIController;
class UParAnimations;

UCLASS()
class PAR_VISUALIZER_API AHumanoid : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHumanoid();
	~AHumanoid();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* input_component) override;


	/*! \brief Adds an action to the current actors animation */
	void AddAction(UAnimMontage*); 

	/*! \brief The getter for an ai_agent*/
	APARAIController *getAIAgent(){ return ai_agent; }

	UPROPERTY(EditAnywhere)
		bool female;

	UParAnimations* getAnimationBlueprint(){ return anim; }
private:
	APARAIController *ai_agent; /*! <A pointer to the ai controlling agent for the pawn*/
	USkeletalMeshComponent *mesh; /*! <A pointer to the mesh. Useful as a shorthand for getting the animation*/
	int idle;/*! <The idle counter that we use to provide new animations*/
	UParAnimations* anim; /*! <The animation handle that links to the animation blueprint*/
	//float ikFootTrace(float, FName);/*! <The helper function for foot-trace IK setup*/
	
};
