/**\file pObject
\brief The base class ApObject for non-agent PAR objects
This class connects meshes to MetaObjects. It also can be initalized to 
set the mesh and coordinates
*/

#pragma once
#include "MetaObject.h"
#include "GameFramework/Actor.h"
#include "pObject.generated.h"

UCLASS()
class PAR_VISUALIZER_API ApObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ApObject();
	~ApObject();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	bool InitalizeObject(const char*, UStaticMeshComponent *, FVector,FVector,FVector);//Initalizes an object based on given parameters

	//Getters of the objects
	MetaObject *getPARObject(){ return obj; }
	UStaticMeshComponent *getMesh(){ return mesh; }
private:
	MetaObject *obj;
	UStaticMeshComponent *mesh;
	
	
};
