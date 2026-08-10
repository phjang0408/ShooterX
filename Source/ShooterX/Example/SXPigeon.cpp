// SXPigeon.cpp

#include "Example/SXPigeon.h"

USXPigeon::USXPigeon()
{
	Name = TEXT("Pigeon");
}

void USXPigeon::Fly()
{
	UE_LOG(LogTemp, Log, TEXT("%s is now flying"), *Name);
}

void USXPigeon::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);	//	부모(UObject)의 Serialize를 먼저 호출 후 사용

	// 마찬가지로 '<<'(시프트 연산자)를 통해, 멤버들을 직렬화 및 역직렬화를 명시
	Ar << Name;
	Ar << ID;
}
