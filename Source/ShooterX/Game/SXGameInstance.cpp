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
	// 새로운 오브젝트 USXObject01
	// 언리얼은 이런식으로 new 키워드를 안쓰고 NewObject<>() API를 사용해야 함.

	// 1. 멤버함수 호출방법
	UE_LOG(LogTemp, Log, TEXT("USXObject01's Name : %s"), *USXObject01->GetObjectName());
	// 우리가 정의한 그냥 멤버함수 호출

	// 2. 리플렉션 시스템을 활용
	// 범위 지정 연산자로 컴파일 타임 호출 => StaticClass()
	FProperty* NameProperty = USXUnrealObject::StaticClass()->FindPropertyByName(TEXT("Name"));	// StaticClass() : 클래스 타입 자체를 가져오는 함수,컴파일 타임 <-> GetClass : 런타임
	FString CompiletimeUSObjectName;
	if (nullptr != NameProperty) {
		NameProperty->GetValue_InContainer(USXObject01, &CompiletimeUSObjectName); // 리플렉션 함수
		UE_LOG(LogTemp, Log, TEXT("CompiletimeUSObjectName: %s"), *CompiletimeUSObjectName);
	}

	// 1. 멤버 함수 호출
	USXObject01->HelloUnreal();

	// 2. 리플렉션 시스템을 활용
	// 포인터 접근 연산자로 런타임에 호출 => GetClass()
	UFunction* HelloUnrealFunction = USXObject01->GetClass()->FindFunctionByName(TEXT("HelloUnreal"));
	if (nullptr != HelloUnrealFunction) {
		USXObject01->ProcessEvent(HelloUnrealFunction, nullptr);	// 리플렉션 함수, nullptr자리는 인자와 반환값이 없을 때 사용하는 방식 : 인자만 있는, 인자+반환값 있는 방식에서 또 다름
	}
}

void USXGameInstance::Shutdown()
{
	Super::Shutdown();

	UE_LOG(LogTemp, Log, TEXT("USXGameInstace::ShutDown() has been called!"));
}
