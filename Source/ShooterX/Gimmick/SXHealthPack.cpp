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

	// [생성자 상황] 에서 사용
	// CreateDefaultSubobject -> SetupAttachment, 등록은 자동 예약
	// CreateDefaultSubobject<T>(FName name) : 타입 T의 컴포넌트나 서브 오브젝트 생성, 고유 식별자(FName)으로 구분
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());

	// 컴포넌트 수정
	BoxComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	BoxComponent->SetRelativeScale3D(FVector(0.6f, 0.8f, 0.8f));
	BoxComponent->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));

	BodyStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyStaticMeshComponent"));
	BodyStaticMeshComponent->SetupAttachment(GetRootComponent());
	
	BodyStaticMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	BodyStaticMeshComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	// 에셋 설정
	// FObjectFinder<T> 변수이름(경로) : 에셋 로딩 기구, 클래스 생성자 안에서만 사용 가능
	// 기본적으로 static 사용(에셋은 한번만 처리하므로)
	// 생성자 전용이므로, 런타임에는 LoadObject나 FStreamableManager를 사용한다.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/LyraResource/Weapons/Healthpack/Mesh/SM_healthpackFull.SM_healthpackFull'"));
	if (true == BodyStaticMesh.Succeeded())
	{
		BodyStaticMeshComponent->SetStaticMesh(BodyStaticMesh.Object);
	}
}