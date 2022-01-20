/**\file ParAnimations.h
	\brief The animation class for Humanoids
	This file provides support for blue-print control of the animations. It also allows 
	us to connect the animation blue-prints to humanoids, and create specific functions
	for other motion controllers.
*/

#pragma once
#include "Humanoid.h"
#include "ParAnimations.generated.h"

/**
 * This is the class that controls all animation blueprint stuff for PAR characters
 */
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class PAR_VISUALIZER_API UParAnimations : public UAnimInstance
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 state_switch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ik_alpha;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool use_left_hand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTransform end_effector;

		void moveCharacter(); /*Moves the character based on it's location, speed, and direction*/
	
	/*The setter and getter for our PAR agent*/
	void setAgent(AHumanoid*);
	AHumanoid *getAgent();
	void update(float delta);

private:
	AHumanoid* agent; /*! <A pointer to the humanoid class, and what all par information goes through. Should be set during each agent's BeginPlay */

};
