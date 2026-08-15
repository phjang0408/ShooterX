// SXHealthPack.cpp

#include "Gimmick/SXHealthPack.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ASXHealthPack::ASXHealthPack() : HealAmount(100.f)
{
	// bCanEverTick : 언리얼의 Tick()함수가 매 프레임 호출할 지 결정
	// true면 수행, flase면 수행하지 않음.
	PrimaryActorTick.bCanEverTick = false;


	// CreateDefaultSubobject<T>(FName name) : 타입 T의 컴포넌트나 서브 오브젝트 생성, 고유 식별자(FName)으로 구분
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	// [생성자 상황] 에서 사용
	// CreateDefaultSubobject -> SetupAttachment
	// 등록은 자동 예약
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());

	BodyStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyStaticMeshComponent"));
	BodyStaticMeshComponent->SetupAttachment(GetRootComponent());

	
}