// SXEagle.cpp

#include "SXEagle.h"

USXEagle::USXEagle()
{
	Name = TEXT("Eagle");
}

void USXEagle::Fly()
{
	UE_LOG(LogTemp, Log, TEXT("%s is flying"), *Name);
}
