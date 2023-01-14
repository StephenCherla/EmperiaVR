// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Engine/DataTable.h"
#include "ShapesInfo.generated.h"

USTRUCT(BlueprintType)
struct FShapesIndexMap : public FTableRowBase {
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Row_Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* StaticMesh;
};
