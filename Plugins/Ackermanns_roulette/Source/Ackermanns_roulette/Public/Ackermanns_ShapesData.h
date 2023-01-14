// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "Ackermanns_ShapesData.generated.h"

/**
 * 
 */
UCLASS()
class ACKERMANNS_ROULETTE_API UAckermanns_ShapesData : public UObject
{
	GENERATED_BODY()
public:
	UAckermanns_ShapesData();

	//Get Number of static meshes in Data table
	int32 GetNumberOfStaticMeshes();

	//Get Static mesh from the Data table at given index
	UStaticMesh* GetStaticMeshFromTable(int32 index);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ShapesData, meta = (AllowPrivateAccess = "true"))
		class UDataTable* ShapesData;
};
