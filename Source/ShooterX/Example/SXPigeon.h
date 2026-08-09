// SXPigeon.h

#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Example/SXFlyable.h"	// 인터페이스 추가
#include "SXPigeon.generated.h"

UCLASS()
class SHOOTERX_API USXPigeon 
	: public UObject		// 순서는 항상 UObject가 먼저
	, public ISXFlyable		// 인터페이스는 그 뒤에
{
	GENERATED_BODY()
public:
	USXPigeon();

	virtual void Fly() override;

private:
	UPROPERTY()
	FString Name;
};