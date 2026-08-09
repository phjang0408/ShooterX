// SXGameInstance.cpp

#include "SXGameInstance.h"
#include "Example/SXFlyable.h"
#include "Example/SXEagle.h"
#include "Example/SXPigeon.h"

USXGameInstance::USXGameInstance()
{	
}

void USXGameInstance::Init()
{
	Super::Init();

	USXPigeon* Pigeon1 = NewObject<USXPigeon>();
	if (IsValid(Pigeon1) == true)
	{
		Pigeon1->Fly();
	}

	USXEagle* Eagle1 = NewObject<USXEagle>();
	if (IsValid(Eagle1) == true)
	{
		Eagle1->Fly();
	}

	// 배열을 하나 생성 - 부모타입(업캐스팅)
	TArray<ISXFlyable*> Birds;
	Birds.Reserve(10);

	// 런타임 객체가, 컴파일 클래스를 통해 본 인터페이스를, 포함하고 있는지 검사
	if (Pigeon1->GetClass()->ImplementsInterface(USXFlyable::StaticClass()) == true)
	{
		ISXFlyable* Bird1 = Cast<ISXFlyable>(Pigeon1);	// 업캐스팅
		Birds.Emplace(Bird1);	// 배열에 삽입
	}

	if (Eagle1->GetClass()->ImplementsInterface(USXFlyable::StaticClass()) == true)
	{
		ISXFlyable* Bird2 = Cast<ISXFlyable>(Eagle1);
		Birds.Emplace(Bird2);
	}

	for (ISXFlyable* Bird : Birds) {
		Bird->Fly();
		// 다형성이지
		// 동시에 의존성 디커플링이라고 함. (부모 입장에선, 작동만 되면 OK)
	}
}

void USXGameInstance::Shutdown()
{
	Super::Shutdown();

	UE_LOG(LogTemp, Log, TEXT("USXGameInstace::ShutDown() has been called!"));
}
