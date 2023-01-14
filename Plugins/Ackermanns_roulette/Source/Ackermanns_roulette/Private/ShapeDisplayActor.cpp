// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeDisplayActor.h"

// Sets default values
AShapeDisplayActor::AShapeDisplayActor()
{
	ShapeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShapeMesh"));
	SetRootComponent(ShapeMesh);
	ShapeMesh->SetRelativeScale3D(FVector(5.0f));
}


// Called when the game starts or when spawned
void AShapeDisplayActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AShapeDisplayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShapeDisplayActor::SetStaticMesh(UStaticMesh* InShapeMesh) {
	ShapeMesh->SetStaticMesh(InShapeMesh);
}