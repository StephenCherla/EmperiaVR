// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ackermanns_Roulette_Manager.generated.h"

UCLASS()
class ACKERMANNS_ROULETTE_API AAckermanns_Roulette_Manager : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AAckermanns_Roulette_Manager();
	~AAckermanns_Roulette_Manager();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		class UHttpService* httpService;
	UPROPERTY(VisibleAnywhere)
		class UAckermanns_ShapesData* shapeDataObj;
	UPROPERTY(VisibleAnywhere)
		class AShapeDisplayActor* shapeDisplayActor;

	AShapeDisplayActor* AAckermanns_Roulette_Manager::SpawnDisplayActor();

	UFUNCTION(CallInEditor)
		void OnRandomNumberAPIResponse(int32 responseIndex);

	UFUNCTION(BlueprintCallable)
		void OnGenerateClicked();

	UFUNCTION(BlueprintCallable)
		void OnManagerInitialize();

	UFUNCTION(BlueprintCallable)
		void OnManagerExit();

};
