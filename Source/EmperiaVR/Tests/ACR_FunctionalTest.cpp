// Fill out your copyright notice in the Description page of Project Settings.


#include "ACR_FunctionalTest.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "HttpService.h"


#if WITH_DEV_AUTOMATION_TESTS

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

#endif