// SXPigeon.cpp

#include "Example/SXPigeon.h"

USXPigeon::USXPigeon()
{
	Name = TEXT("Pigeon");
}

void USXPigeon::Fly()
{
	UE_LOG(LogTemp, Log, TEXT("%s is now flying"), *Name);
	
	// Fly함수에선, OnPigeonFlying 델리게이트에 대해 Broadcast를 수행하려 한다.
	// 인자들 적절히 넣어주고 실행하면, OnPigeionFlying 구독한 애들이, 호출을 받게 된다.
	OnPigeonFlying.Broadcast(*Name, ID);
}

void USXPigeon::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);	//	부모(UObject)의 Serialize를 먼저 호출 후 사용

	// 마찬가지로 '<<'(시프트 연산자)를 통해, 멤버들을 직렬화 및 역직렬화를 명시
	Ar << Name;
	Ar << ID;
}
