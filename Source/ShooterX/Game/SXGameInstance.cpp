// SXGameInstance.cpp

#include "SXGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SXUnrealObject.h"	// SXUnrealObject추가

USXGameInstance::USXGameInstance()
{
	Name = TEXT("SXGameInstance's Class Default Object");		
}

void USXGameInstance::Init()
{
	Super::Init();

	USXUnrealObject* USXObject01 = NewObject<USXUnrealObject>();
	// 언리얼은 이런식으로 new 키워드를 안쓰고 NewObject<>() API를 사용해야 함.

	// 1. 멤버함수 호출방법
	UE_LOG(LogTemp, Log, TEXT("USXObject01's Name : %s"), *USXObject01->GetObjectName());
	// 우리가 정의한 그냥 멤버함수 호출

	// 2. 리플렉션 시스템을 활용
	FProperty* NameProperty = USXUnrealObject::StaticClass()->FindPropertyByName(TEXT("Name"));
	FString CompiletimeUSObjectName;
	if (nullptr != NameProperty) {
		NameProperty->GetValue_InContainer(USXObject01, &CompiletimeUSObjectName);
		UE_LOG(LogTemp, Log, TEXT("CompiletimeUSObjectName: %s"), *CompiletimeUSObjectName);
	}

	// 1. 멤버 함수 호출
	USXObject01->HelloUnreal();

	// 2. 리플렉션 시스템을 활용
	UFunction* HelloUnrealFunction = USXObject01->GetClass()->FindFunctionByName(TEXT("HelloUnreal"));
	if (nullptr != HelloUnrealFunction) {
		USXObject01->ProcessEvent(HelloUnrealFunction, nullptr);
	}
}

void USXGameInstance::Shutdown()
{
	Super::Shutdown();

	UE_LOG(LogTemp, Log, TEXT("USXGameInstace::ShutDown() has been called!"));
}
