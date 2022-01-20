// Fill out your copyright notice in the Description page of Project Settings.
#include "pObject.h"



extern TMap<int32, ApObject*> all_objects;

// Sets default values
ApObject::ApObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	obj = NULL;
	mesh = NULL;
}

ApObject::~ApObject(){
	delete obj;
}
// Called when the game starts or when spawned
void ApObject::BeginPlay()
{
	Super::BeginPlay();
	obj = new MetaObject(std::string(TCHAR_TO_ANSI(*this->GetName())).c_str());
	//We do one of these to make sure that we start with the proper information
	FVector trans = this->GetActorLocation();
	Vector<3> *vec = new Vector < 3 >();
	vec->v[0] = trans.X;
	vec->v[1] = trans.Y;
	vec->v[2] = trans.Z;
	this->obj->setPosition(vec);
	trans = this->GetActorQuat().Euler();
	vec->v[0] = trans.X;
	vec->v[1] = trans.Y;
	vec->v[2] = trans.Z;
	this->obj->setOrientation(vec);
	trans = this->GetActorScale();
	vec->v[0] = trans.X;
	vec->v[1] = trans.Y;
	vec->v[2] = trans.Z;
	this->obj->setBoundingPoint(vec, 0);
	all_objects.Emplace(obj->getID(), this);

}
/******************************************************************************
 *Allows us to create an ApObject from another process, like if the system is
 *reading a text file
 *****************************************************************************/
bool ApObject::InitalizeObject(const char* name, 
	UStaticMeshComponent *in_mesh, 
	FVector pos, 
	FVector rot,
	FVector scale){
	this->Rename(ANSI_TO_TCHAR(name));
	this->mesh = in_mesh;
	this->SetActorLocation(pos);
	this->SetActorRotation(FQuat::MakeFromEuler(rot));
	this->SetActorScale3D(scale);
	return true;
}

// Called every frame
void ApObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	FVector trans = this->GetActorLocation();
	Vector<3> *vec = new Vector < 3 >();
	vec->v[0] = trans.X;
	vec->v[1] = trans.Y;
	vec->v[2] = trans.Z;
	this->obj->setPosition(vec);
	trans = this->GetActorQuat().Euler();
	vec->v[0] = trans.X;
	vec->v[1] = trans.Y;
	vec->v[2] = trans.Z;
	this->obj->setOrientation(vec);

}

