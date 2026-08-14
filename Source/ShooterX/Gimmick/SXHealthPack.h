// SXHealthPack.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SXHealthPack.generated.h"

UCLASS()
class SHOOTERX_API ASXHealthPack : public AActor
{
	GENERATED_BODY()
	
private:
	// EditInstanceOnly : 객체에서만 수정 가능(레벨에 배치한 객체에서 Details에서 검색 가능)
	// BlueprintReadWrite : BP에서 변수를 Get,Set 가능 (ReadOnly는 Get만 가능)
	// Meta = (AllowPrivateAccess) : private 접근 지정자이지만, 접근을 할 수 있게 해줌.
	// Category = "ShooterX|SXHealthPack" : 카테고리에 탭을 생성, |로 하면 하위폴더의 개념
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess),  Category = "ShooterX|SXHealthPack")
	float HealAmount;

	// bool bIsUsed
	uint8 bIsUsed : 1;
};
