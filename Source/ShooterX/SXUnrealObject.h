// SXUrealObject

#pragma once							// 헤더파일 순환참조 방지

// 헤더파일의 순서는 항상 중요!

#include "CoreMinimal.h"				// 언리얼 자주 사용하는 기본 타입과 기능을 포함한 최소 공용 헤더
#include "UObject/Object.h"				// 부모 클래스의 헤더파일(ex. 액터라면 AActor)
#include "SXUnrealObject.generated.h"	// UHT에 의해 생성된 .generated.h, 빌드 과정에서 무조건 생성. 순서는 항상 맨 마지막!

/**
 * 
 */
UCLASS()	// 언리얼 클래스 선언 전에 반드시 작성해야하는 매크로 : 구조체 = USTRUCT(), 열거체 = UENUM() -> 리플렉션 대상임을 UHT에 알리는 매크로
class SHOOTERX_API USXUnrealObject : public UObject		// UObject상속 = 언리얼 오브젝트만의 기능이 지원됨(가비지 컬렉션, 리플렉션 ...)
	// SHOOTERX_API = 이 키워드가 없으면, 다른 모듈에서 해당 클래스에 접근할 수 없음(모듈 간 public)
	// UObject를 상속하기에, 앞에 U를 붙임
{
	GENERATED_BODY()	// UObject안의 기능들(가비지컬렉션, Reflection 등)이 동작하기위한 매크로 : UFUNCTION, UPROPERTY같은 매크로가 존재
};
