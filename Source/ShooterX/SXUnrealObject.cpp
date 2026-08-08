// SXUnrealObject.cpp

#include "SXUnrealObject.h"

USXUnrealObject::USXUnrealObject()
{
	Name = TEXT("USXUnrealObject CDO"); // CDO의 초기화는 생성자!
}

void USXUnrealObject::HelloUnreal()
{
	UE_LOG(LogTemp, Log, TEXT("USXUnrealObject::HelloUnreal() has been called."));
}
