// Fill out your copyright notice in the Description page of Project Settings.
#include "pObjectComponent.h"
#include "MetaObject.h"
#include "actionary.h"

extern Actionary *actionary;

UpObjectComponent::UpObjectComponent(){
	obj = NULL;
}

void UpObjectComponent::BeginPlay()
{
	Super::BeginPlay();
	std::string str = std::string(TCHAR_TO_ANSI(*this->GetOwner()->GetName()));
	try{
		obj = new MetaObject(str.c_str());
	}
	catch (int e){
		obj = NULL;
		e = 1;
	}
	//We do one of these to make sure that we start with the proper information
	if (obj != NULL){
		FVector trans = this->GetOwner()->GetActorLocation();
		Vector<3> *vec = new Vector < 3 >();
		vec->v[0] = trans.X;
		vec->v[1] = trans.Y;
		vec->v[2] = trans.Z;
		this->obj->setPosition(vec);
		trans = this->GetOwner()->GetActorQuat().Euler();
		vec->v[0] = trans.X;
		vec->v[1] = trans.Y;
		vec->v[2] = trans.Z;
		this->obj->setOrientation(vec);
		trans = this->GetOwner()->GetActorScale();
		vec->v[0] = trans.X;
		vec->v[1] = trans.Y;
		vec->v[2] = trans.Z;
		this->obj->setBoundingPoint(vec, 0);
		//all_objects.Emplace(obj->getID(), this);
		PrimaryComponentTick.bCanEverTick = true;
	}
}

