// Fill out your copyright notice in the Description page of Project Settings.


#include "Ackermanns_Roulette_Manager.h"
#include "ShapeDisplayActor.h"
#include "Kismet/GameplayStatics.h"
#include "HttpService.h"
#include "Ackermanns_ShapesData.h"
// Sets default values
AAckermanns_Roulette_Manager::AAckermanns_Roulette_Manager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AAckermanns_Roulette_Manager::~AAckermanns_Roulette_Manager()
{

}

// Called when the game starts or when spawned
void AAckermanns_Roulette_Manager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAckermanns_Roulette_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AShapeDisplayActor* AAckermanns_Roulette_Manager::SpawnDisplayActor()
{
	FVector Location(0.0f, 0.0f, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	UWorld* World = GEditor->GetEditorWorldContext().World();
	return World->SpawnActor<AShapeDisplayActor>(Location, Rotation, SpawnInfo);
}

//Instantiate the Objects and actors here
void AAckermanns_Roulette_Manager::OnManagerInitialize()
{
	httpService = NewObject<UHttpService>();
	httpService->SetHttpModule();
	httpService->OnRandomNumberAPIResponse.AddDynamic(this, &AAckermanns_Roulette_Manager::OnRandomNumberAPIResponse);

	shapeDataObj = NewObject<UAckermanns_ShapesData>();
	shapeDisplayActor = SpawnDisplayActor();
}

//Callback from httpservice
void AAckermanns_Roulette_Manager::OnRandomNumberAPIResponse(int32 responseIndex) {
	UE_LOG(LogTemp, Warning, TEXT("[AAckermanns_Roulette_Manager::OnRandomNumberAPIResponse : %d"), responseIndex);
	if (IsValid(shapeDisplayActor) && IsValid(shapeDataObj))
		shapeDisplayActor->SetStaticMesh(shapeDataObj->GetStaticMeshFromTable(responseIndex));
}

//Callback from UI
void AAckermanns_Roulette_Manager::OnGenerateClicked()
{
	if (IsValid(httpService) && IsValid(shapeDataObj)) {
		bool bIsApiCalled = false;
		httpService->GetRandomIntFromAPI(0, shapeDataObj->GetNumberOfStaticMeshes() - 1, bIsApiCalled);
	}
}

//Remove the Objects and actors here
void AAckermanns_Roulette_Manager::OnManagerExit()
{
	if (IsValid(httpService)) httpService->ConditionalBeginDestroy();
	if (IsValid(shapeDataObj)) shapeDataObj->ConditionalBeginDestroy();
	if (IsValid(shapeDisplayActor)) shapeDisplayActor->Destroy();
	Destroy();
}

