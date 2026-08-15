// SXHealthPack.cpp

#include "Gimmick/SXHealthPack.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ASXHealthPack::ASXHealthPack() : HealAmount(100.f)
{
	// Tick 함수를 쓸 예정이니 true로 설정
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());

	BoxComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	BoxComponent->SetRelativeScale3D(FVector(0.6f, 0.8f, 0.8f));
	BoxComponent->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));

	BodyStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyStaticMeshComponent"));
	BodyStaticMeshComponent->SetupAttachment(GetRootComponent());
	
	BodyStaticMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	BodyStaticMeshComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/LyraResource/Weapons/Healthpack/Mesh/SM_healthpackFull.SM_healthpackFull'"));
	if (true == BodyStaticMesh.Succeeded())
	{
		BodyStaticMeshComponent->SetStaticMesh(BodyStaticMesh.Object);
	}
}

void ASXHealthPack::BeginPlay()
{
	// AActor의 BeginPlay를 먼저 실행한 후 진행한다.
	Super::BeginPlay();

	// 배치된 액터의 위치를 StartLocation(FVector)로 구해 변수로 만들어둔다.
	StartLocation = GetActorLocation();	
}

void ASXHealthPack::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// FMath::Sin(시간) -> 시간을 기반으로 -1.0 ~ +1.0을 반환한다.
	// 시간에는 [누적시간 * 속도] 형태로 곱해준다.
	// 여기에 -1 ~ 1 범위니까, 진폭을 또 곱해줘서 높낮이를 맞춰준다.
	ElapsedTime += DeltaSeconds;
	const float ZOffset = FMath::Sin(ElapsedTime * MovementSpeed) * Amplitude;

	// 변수로 만들어 둔 원래 위치에, ZOffset을 더해, 새로운 위치로 지정해준다.
	FVector NewLocation = StartLocation;
	NewLocation.Z += ZOffset;
	SetActorLocation(NewLocation);
}

