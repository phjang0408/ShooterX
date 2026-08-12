// SXPigeon.h

#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Example/SXFlyable.h"	
#include "SXPigeon.generated.h"

// 델리게이트 타입 생성
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPigeonFlying, const FString&, InName, const int32, InID);

USTRUCT()
struct FSXPigeonData	// USTRUCT()키워드에, 접두사 F가 빠지면 에러
{
	GENERATED_BODY()

public:
	FSXPigeonData() {}
	FSXPigeonData(const FString& InName, int32 InID)
		: Name(InName)  // 언리얼 코딩 컨벤션에는 입력 전용 매개변수명에 In-을 붙힘. 
		, ID(InID)		// 출력 전용은 Out-, 입출력은 InOut
	{	}

	friend FArchive& operator<<(FArchive& InArchive, FSXPigeonData& InPigeonData)
	{
		InArchive << InPigeonData.Name;
		InArchive << InPigeonData.ID;
		return InArchive;
	}

private:
	UPROPERTY()
	FString Name;
	UPROPERTY()
	int32 ID;
};

UCLASS()
class SHOOTERX_API USXPigeon 
	: public UObject		// 순서는 항상 UObject가 먼저
	, public ISXFlyable		// 인터페이스는 그 뒤에
{
	GENERATED_BODY()
public:
	USXPigeon();

	virtual void Fly() override;
	// 앞 const : 반환값 const, 뒤 const : 이 객체의 필드수정불가용 const
	const FString& GetPigeonName() const { return Name; }

	void SetPigeonName(const FString& InName) { Name = InName; }
	
	int32 GetPigeonID() const { return ID; }
	
	void SetPigeonID(const int32& InID) { ID = InID; }

	// 방법 2) Serialize()함수
	// 구조체를 따로 빼지 않고도 가능
	virtual void Serialize(FArchive& Ar) override;


public:
	// 델리게이트 변수를 필드로서 선언
	// FOnPigeonFlying 타입을 쓰는 델리게이트에 변수를 만듬
	FOnPigeonFlying OnPigeonFlying;	

private:
	UPROPERTY()
	FString Name;
	UPROPERTY()
	int32 ID;
};