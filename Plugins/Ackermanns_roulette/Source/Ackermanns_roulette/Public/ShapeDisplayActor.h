// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShapeDisplayActor.generated.h"

UCLASS()
class ACKERMANNS_ROULETTE_API AShapeDisplayActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShapeDisplayActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* ShapeMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetStaticMesh(UStaticMesh* InShapeMesh);

};
