#include "Ackermanns_ShapesData.h"
#include "Data/ShapesInfo.h"

UAckermanns_ShapesData::UAckermanns_ShapesData() {
	static ConstructorHelpers::FObjectFinder<UDataTable> ShapesDataObject(TEXT("DataTable'/Ackermanns_roulette/Data/DataTables/DT_Shapes.DT_Shapes'"));
	if (ShapesDataObject.Succeeded())
	{
		ShapesData = ShapesDataObject.Object;
	}
};

int32 UAckermanns_ShapesData::GetNumberOfStaticMeshes()
{
	return ShapesData->GetRowNames().Num();
}

UStaticMesh* UAckermanns_ShapesData::GetStaticMeshFromTable(int32 index)
{
	TArray<FName> RowNames = ShapesData->GetRowNames();
	for (FName RowName : RowNames) {
		FShapesIndexMap* Item = ShapesData->FindRow<FShapesIndexMap>(RowName, "");
		if (index == Item->Row_Index) {
			return Item->StaticMesh;
		}
	}
	return nullptr;
}