// Fill out your copyright notice in the Description page of Project Settings.
#include "Humanoid.h"
//#include "PAR_Visualizer.h"
#include "ParAnimations.h"
#include "PARAIController.h"

extern TArray<AHumanoid*> all_agents;

/*https://wiki.unrealengine.com/Trace_Functions*/
/*FORCEINLINE bool Trace(
	UWorld* World,
	AActor* ActorToIgnore,
	const FVector& Start,
	const FVector& End,
	FHitResult& HitOut,
	ECollisionChannel CollisionChannel = ECC_Pawn,
	bool ReturnPhysMat = false
	) {
	if (!World)
	{
		return false;
	}

	FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
	TraceParams.bTraceComplex = true;
	//TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

	//Ignore Actors
	TraceParams.AddIgnoredActor(ActorToIgnore);

	//Re-initialize hit info
	HitOut = FHitResult(ForceInit);

	//Trace!
	World->LineTraceSingle(
		HitOut,		//result
		Start,	//start
		End, //end
		CollisionChannel, //collision channel
		TraceParams
		);

	//Hit any Actor?
	return (HitOut.GetActor() != NULL);
}*/



// Sets default values
AHumanoid::AHumanoid() :ai_agent(NULL), mesh(NULL), idle(0), female(false), anim(NULL)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AHumanoid::~AHumanoid(){
	if (ai_agent != NULL){
		//ai_agent->cleanPAR();
		}
}

// Called when the game starts or when spawned
void AHumanoid::BeginPlay()
{
	Super::BeginPlay();
	this->mesh = this->GetMesh();
	if (ai_agent == NULL){
		ai_agent = Cast<APARAIController>(this->GetController());
	}
	if (ai_agent != NULL){
		ai_agent->initPARAgent(std::string(TCHAR_TO_ANSI(*this->GetName())), this->GetActorLocation(), this->GetActorQuat().Euler(), this->GetActorScale());
	}
	//We also supply the PAR agent to the animation system. Later this may change to providing an AHumanoid to the animation system if need-be
	if (mesh != NULL){
		anim = Cast<UParAnimations>(mesh->GetAnimInstance());//This converts the animation blueprint into a class for us
		if (anim != NULL && ai_agent != NULL){
			anim->setAgent(this);
			if (female)
				anim->state_switch = 1;
		}
	}
	all_agents.Emplace(this);
}

// Called every frame
void AHumanoid::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (anim != NULL){
		anim->update(DeltaTime);
	}
	if (ai_agent != NULL){
		if (ai_agent->isIdle())
			idle++;
		if (idle == 10)
			if (ai_agent->runDefaultAction())
				idle = 0;
		
		ai_agent->setPosition(this->GetActorLocation());
		}
	}

//!This function starts playing an animation montage on our character, and is useful for displaying animation
/*!
	\param montage The montage we wish to play on the agent.
*/
void AHumanoid::AddAction(UAnimMontage *montage){
	if (mesh != NULL && montage != NULL){
		if (anim != NULL){
			mesh->AnimScriptInstance->Montage_Play(montage, 1.0f);
		}
	}
}

// Called to bind functionality to input
void AHumanoid::SetupPlayerInputComponent(UInputComponent* input_component)
{
	Super::SetupPlayerInputComponent(input_component);

}

/*float AHumanoid::ikFootTrace(float trace_distance, FName socket){
	float ik_offset = 0.0f;
	FVector soc_loc = mesh->GetSocketLocation(socket);
	FVector start_vec = FVector(this->GetActorLocation().X, this->GetActorLocation().Y, soc_loc.Z);
	FVector end_vec = FVector(this->GetActorLocation().X, this->GetActorLocation().Y, soc_loc.Z - trace_distance);
	//The trace data is stored here
	FHitResult HitData(ForceInit);
	if (Trace(GetWorld(), this, start_vec, end_vec, HitData)) //If we hit something
	{
		FVector result = HitData.Location - end_vec;
		ik_offset = result.Size();
	}
	return ik_offset;
}*/
