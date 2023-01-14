// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpService.h"
UHttpService::UHttpService() {

}

void UHttpService::SetHttpModule() {
	Http = &FHttpModule::Get();
}

void UHttpService::SetAppServerBaseURL(FString InVal)
{
	if (!InVal.IsEmpty())
	{
		ApiBaseUrl = InVal;
	}
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> UHttpService::RequestWithRoute(FString Subroute) {
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	FString url = ApiBaseUrl + Subroute;
	Request->SetURL(*url);
	SetRequestHeaders(Request);
	UE_LOG(LogTemp, Warning, TEXT("[UHttpService::RequestWithRoute]Request URL: %s"), *url);
	return Request;
}

void UHttpService::SetRequestHeaders(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request) {
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	//Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	//Request->SetHeader(TEXT("Accept"), TEXT("application/json"));

}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> UHttpService::GetRequest(FString Subroute) {
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = RequestWithRoute(Subroute);
	Request->SetVerb("GET");
	return Request;
}

TSharedRef<IHttpRequest, ESPMode::ThreadSafe> UHttpService::PostRequest(FString Subroute, FString ContentJsonString) {
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = RequestWithRoute(Subroute);
	Request->SetVerb("POST");
	Request->SetContentAsString(ContentJsonString);
	return Request;
}

void UHttpService::Send(TSharedRef<IHttpRequest, ESPMode::ThreadSafe>& Request) {
	Request->ProcessRequest();
}

bool UHttpService::ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful) {
	if (!bWasSuccessful || !Response.IsValid()) return false;
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode())) return true;
	else {
		UE_LOG(LogTemp, Warning, TEXT("Http Response returned error code: %d"), Response->GetResponseCode());
		UE_LOG(LogTemp, Warning, TEXT("Http Response returned error content: %s"), *Response->GetContentAsString());
		return false;
	}
}

void UHttpService::GetRandomIntFromAPI(int32 minSize, int32 databaseSize, bool& InRequestResult)
{
	if (databaseSize < 0 || (minSize > databaseSize)) {
		InRequestResult = false;
		return;
	}

	//Constructing The URL for RandomNumberAPI
	TArray<FStringFormatArg> args;
	args.Add(FStringFormatArg(FString::Printf(TEXT("random"))));
	args.Add(FStringFormatArg(FString::Printf(TEXT("min=%s"), *FString::FromInt(minSize))));
	args.Add(FStringFormatArg(FString::Printf(TEXT("max=%s"), *FString::FromInt(databaseSize))));
	args.Add(FStringFormatArg(FString::Printf(TEXT("count=1"))));

	FString formattedStr = FString::Format(TEXT("{0}?{1}&{2}&{3}"), args);
	UE_LOG(LogTemp, Warning, TEXT("[UHttpService::GetRandomIntFromAPI] formattedStr URL: %s"), *formattedStr);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = GetRequest(formattedStr);
	Request->OnProcessRequestComplete().BindUObject(this, &UHttpService::GetRandomIntFromAPIResponse);
	Send(Request);
	InRequestResult = true;
	IsResponseReceived = false;
	return;
}

void UHttpService::GetRandomIntFromAPIResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	IsResponseReceived = bWasSuccessful;
	if (!ResponseIsValid(Response, bWasSuccessful)) return;
	//Using Fstring Modifiers because response is not in json format
	FString resStr = Response->GetContentAsString();
	resStr.RemoveFromStart(TEXT("["));
	resStr.RemoveFromEnd(TEXT("]"));
	TArray<FString> res;
	resStr.ParseIntoArray(res, TEXT(","), true);
	int32 responseIndex = FCString::Atoi(*res[0]);
	UE_LOG(LogTemp, Warning, TEXT("[UHttpService::GetRandomIntFromAPIResponse]responseIndex : %d"), responseIndex);
	OnRandomNumberAPIResponse.Broadcast(responseIndex);
	//Call back to the Display Actor
	/*if (IsValid(ShapeDisplayActor)) {
		ShapeDisplayActor->OnRandomAPIServerResponse(responseIndex);
	}*/
}
