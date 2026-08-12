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

	// 선언된 새 프로퍼티에, 객체를 집어넣어줌.
	SpawnedPigeon = NewObject<USXPigeon>();
	SpawnedPigeon->SetPigeonName(TEXT("SpawnedPigeon"));
	SpawnedPigeon->SetPigeonID(7);

	// IsAlreadyBound로 검증 및 구독
	// OnPigeonFlying은 USXPigeon 클래스의 멤버,
	// SpawnedPigeon 객체는, 이 멤버에 대해서, 구독하는 객체이자 발행하는 객체가 될 거임
	if (false == SpawnedPigeon->OnPigeonFlying.IsAlreadyBound(this, &ThisClass::HandlePigeonFlying))
	{
		SpawnedPigeon->OnPigeonFlying.AddDynamic(this, &ThisClass::HandlePigeonFlying);
	}
	// 실제 실행
	// Fly() 함수 내에서 OnPigeonFlying.Broadcast(*Name, ID);를 실행함.
	// 즉, 이걸 구독하고 있는 애들에게 Broadcast하고, SpawnedPigeon 본인도 구독했으니 '콜백 함수'를 실행함
	SpawnedPigeon->Fly();
}

void USXGameInstance::Shutdown()
{
	UE_LOG(LogTemp, Log, TEXT("USXGameInstace::ShutDown() has been called!"));

	// 연결 끊는곳은 실행 종료 시가 적절
	// IsAlreadyBound로 검증 및 구독 취소
	if (true == SpawnedPigeon->OnPigeonFlying.IsAlreadyBound(this, &ThisClass::HandlePigeonFlying))
	{
		SpawnedPigeon->OnPigeonFlying.RemoveDynamic(this, &ThisClass::HandlePigeonFlying);
	}
	Super::Shutdown();

	
}

// 콜백함수 구현
void USXGameInstance::HandlePigeonFlying(const FString& InName, const int32 InID)
{
	// 발행자에서 Execute나 BroadCast가 실행되면, 얘가 실행 됨
	UE_LOG(LogTemp, Log, TEXT("SubScribed Function Call! [%d] %s is flying~~"), InID, *InName);
}