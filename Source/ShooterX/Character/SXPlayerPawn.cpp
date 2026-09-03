// SXPlayerPawn.cpp

#include "Character/SXPlayerPawn.h"
#include "Components/CapsuleComponent.h"		// CapsuleComponent
#include "Components/SkeletalMeshComponent.h"	// SkeletalMeshComponent
#include "GameFramework/FloatingPawnMovement.h"	// FloatingPawnMovement
#include "GameFramework/SpringArmComponent.h"	// SpringArmComponent
#include "Camera/CameraComponent.h"				// CamreaComponent

ASXPlayerPawn::ASXPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	// CapsuleComponent 객체 생성, 루트 설정, 초기화
	float CharacterHalfHeight = 90.f;	// 캐릭터의 키의 절반 (180 / 2)
	float CharacterRadius = 40.f;		// 캐릭터의 둘레
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetCapsuleHalfHeight(CharacterHalfHeight);
	CapsuleComponent->SetCapsuleRadius(CharacterRadius);
	// or CapsuleComponent->InitCapsuleSize(40.f, 40.f);

	// SkeletalMeshComponent 생성, 부착, 초기화
	FVector PivotPosition(0.f, 0.f, -CharacterHalfHeight);
	FRotator PivotRotation(0.f, -90.f, 0.f);		// 모델링툴과 언리얼 툴의 방향은 다르기에, 방향도 바꿔줘야함.
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetRelativeLocationAndRotation(PivotPosition, PivotRotation);

	// C++에서 Skeletal Mesh 에셋을 불러오는방법(아님 에디터 Mesh탭에서 지정해줘도 됨)
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("오브젝트 패스"));
	//if (true == SkeletalMeshAsset.Succeeded())
	//{
	//    SkeletalMeshComponent->SetSkeletalMesh(SkeletalMeshAsset.Object);
	//}

	// SpringArmComponent
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 400.f;
	SpringArmComponent->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f)); // 아래로 15도

	// CameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CamreaComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);	// SpringArm에 Attach

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

void ASXPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	// AnimationMode를 설정한다 : SIngleMode로 설정
	SkeletalMeshComponent->SetAnimationMode(EAnimationMode::AnimationSingleNode);

	UAnimationAsset* AnimationSequenceAsset = LoadObject<UAnimationAsset>(SkeletalMeshComponent, TEXT("/Script/Engine.AnimSequence'/Game/LyraResource/Characters/Heroes/Mannequin/Animations/Locomotion/Unarmed/MF_Unarmed_Jog_Fwd.MF_Unarmed_Jog_Fwd'"));
	if (IsValid(AnimationSequenceAsset) == true) {
		SkeletalMeshComponent->PlayAnimation(AnimationSequenceAsset, true);
	}
}

void ASXPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);	// override할 때는 항상 Super먼저!

	//BindAxis(Axis Mappings에서 설정한 이름, 바인딩 할 객체, 그 객체에서 호출되는 함수)
	PlayerInputComponent->BindAxis(TEXT("FrontRear"), this, &ThisClass::GOFrontRear);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ThisClass::GOLeftRight);
}

void ASXPlayerPawn::GOFrontRear(float InAxisValue)
{
	// AddMovementInput(WorldDirection, Scale) : 방향에, 크기를 더해 이동
	AddMovementInput(GetActorForwardVector(), InAxisValue);
}

void ASXPlayerPawn::GOLeftRight(float InAxisValue)
{
	AddMovementInput(GetActorRightVector(), InAxisValue);
}
