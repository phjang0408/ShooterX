// SXFlyable.h

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SXFlyable.generated.h"

// 1. U로 시작하는 "타입 클래스"
// UHT에게, 내가 존재한다고 알리는 역할 딱 하나 : 리플렉션(타입 정보)등을 등록용도
// 런타임에서 타입 체크(Imple...), BP에서 구현하라고 노출, Cast같은 캐스팅이 '가능'해짐
// 실제로는 잘 사용 X
UINTERFACE(MinimalAPI)
class USXFlyable : public UInterface {
	GENERATED_BODY()
};

// 2. I로 시작하는 "인터페이스 클래스"
// 진짜 인터페이스, UInterface를 상속받지 않음.
// 객체를 설계(로직 작성)할 때 사용
// 설계할 때, Unreal은 '선언과 동시에 정의'도 가능함
class SHOOTERX_API ISXFlyable {
	GENERATED_BODY()

public:
	virtual void Fly() = 0;	// 순수 가상 함수로 사용, 보통 이렇게
};

/* U와 I가 분리된 이유
: UInterface를 상속받는 '타입 클래스'만 사용하면,
이 인터페이스를 상속받는 액터나 클래스가 AActor, UObject를 상속받지 못함!
Why? UInterface는 UObject의 자식이라, '다중상속'이 되어버림 : 다이아몬드 문제
==> 이를 피하기 위해 UInterface를 상속받지 않는, '인터페이스 클래스'를 사용함
*/