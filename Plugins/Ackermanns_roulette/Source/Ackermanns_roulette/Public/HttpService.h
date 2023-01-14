// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "HttpService.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRandomNumberAPIResponse, int32, responseIndex);
/**
 *
 */
UCLASS()
class ACKERMANNS_ROULETTE_API UHttpService : public UObject
{
	GENERATED_BODY()
public:

	FHttpModule* Http;
	FString ApiBaseUrl = "http://www.randomnumberapi.com/api/v1.0/";

	UHttpService();
	//Instantiating HTTP Module
	void SetHttpModule();
	//Function to Set Base Url
	void SetAppServerBaseURL(FString InVal);
	FString AuthorizationHeader = TEXT("Authorization");
	//Generic HTTP SERVICES
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> RequestWithRoute(FString Subroute);
	void SetRequestHeaders(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GetRequest(FString Subroute);
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> PostRequest(FString Subroute, FString ContentJsonString);
	void Send(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request);

	bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful);

	//CallingAPIServerHere
	UFUNCTION(BlueprintCallable, Category = "HTTP Request")
		void GetRandomIntFromAPI(int32 minSize, int32 databaseSize, bool& InRequestResult);
	//CallbackfromAPIServer
	void GetRandomIntFromAPIResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY()
		FOnRandomNumberAPIResponse OnRandomNumberAPIResponse;
	//Params used for functionalUnitTesting
	bool IsResponseReceived = false;
};
