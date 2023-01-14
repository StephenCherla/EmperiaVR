// Fill out your copyright notice in the Description page of Project Settings.


#include "ACR_FunctionalTest.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "HttpService.h"


#if WITH_DEV_AUTOMATION_TESTS
//Unit test for valid request
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHttpServiceTest_ValidData, "AcR_Plugin.HttpServiceTest.ValidRequestTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FHttpServiceTest_ValidData::RunTest(const FString& Parameters)
{
	UHttpService* HttpService = NewObject<UHttpService>();
	bool test;
	HttpService->GetRandomIntFromAPI(0, 10, test);

	TestEqual(TEXT("Api service should be called when there is data in datatable"), true, test);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHttpServiceTest_InvalidData, "AcR_Plugin.HttpServiceTest.InvalidRequestTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FHttpServiceTest_InvalidData::RunTest(const FString& Parameters)
{
	UHttpService* HttpService = NewObject<UHttpService>();
	bool test;
	HttpService->GetRandomIntFromAPI(0, -1, test);


	TestEqual(TEXT("Api service should not be called when there is no data in datatable"), false, test);
	return true;
}

//Unit test for valid response when valid request is sent
DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSetupHttpService, UHttpService*, HttpService);
bool FSetupHttpService::Update()
{
	HttpService->SetHttpModule();
	bool test;
	HttpService->GetRandomIntFromAPI(0, 10, test);
	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FHttpServiceTest_Response, FAutomationTestBase*, Test, UHttpService*, HttpService);
bool FHttpServiceTest_Response::Update()
{

	Test->TestEqual("Api service should send a response when valid request is sent", true, HttpService->IsResponseReceived);
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHttpServiceTest_RequestAndResponseTest, "AcR_Plugin.HttpServiceTest.RequestAndResponseTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)
bool FHttpServiceTest_RequestAndResponseTest::RunTest(const FString& Parameters)
{

	UHttpService* HttpService = NewObject<UHttpService>();
	ADD_LATENT_AUTOMATION_COMMAND(FSetupHttpService(HttpService));
	ADD_LATENT_AUTOMATION_COMMAND(FWaitLatentCommand(10.0f));
	ADD_LATENT_AUTOMATION_COMMAND(FHttpServiceTest_Response(this, HttpService));
	return true;
}

#endif