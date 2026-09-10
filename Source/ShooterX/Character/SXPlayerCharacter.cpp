// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SXPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//Input부분 Header
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/SXInputConfig.h"
#include "Kismet/KismetSystemLibrary.h"


ASXPlayerCharacter::ASXPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	float CharacterHalfHeight = 90.f;
	float CharacterRadius = 40.f;
	// 1. Capsule 크기 설정
	GetCapsuleComponent()->InitCapsuleSize(CharacterRadius, CharacterHalfHeight);

	// 2. Capsule안에서 Mesh 위치 설정
	FVector PivotPosition(0.f, 0.f, -CharacterHalfHeight);
	FRotator PivotRotation(0.f, 90.f, 0.f);
	GetMesh()->SetRelativeLocationAndRotation(PivotPosition, PivotRotation);

	// 3. SpringArm-Camera 컴포넌트 생성
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->SetRelativeLocation(FVector(0.f, 50.f, 300.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	// 4. 속도, 점프 높이 설정
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	// GetCharacterMovement()->bOrientRotationToMovement = true; : 이동방향으로 카메라가 따라가도록하는 설정
	// GetCharacterMovement()->MaxAcceleration = 2000.f; : 초기 가속도 설정
	// GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; : 입력을 뗐을 때 얼마나 빨리 멈추는지
	// AirControl, .bCanCrouch, CrouchedHalfHeight 등이 있다.
}

// BeginPlay -> IMC 등록
// IMC는 'LocalPlayer가 가진 EnhancedInputLocalPlayerSubsystem'에 등록한다.
void ASXPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 1. Character -> Controller로 Cast
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (IsValid(PlayerController) == true)
	{	
		// 2. Controller에서 LocalPlayer 접근 후, 그 LocalPlayer의 UEnhancedInputLocalPlayerSubsysystem을 가져옴.
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (IsValid(Subsystem))
		{	// 3. 가져온 UEnhancedInputLocalPlayerSubsystem에 IMC를 등록!
			Subsystem->AddMappingContext(PlayerCharacterInputMappingContext, 0);
		}
	}
}

// SetupPlayerInputComponent -> IA와 함수들을 연결
// IA_Move와 InputMove()를 연결
void ASXPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 1. 기존 UInputComponent를 EnhancedInputComponent로 Cast 후,
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent) == true)
	{	// 2. BindAction함수를 통해, "Move IA가 Triggered로 발생하면, this에서 InputMove 함수를 실행한다."로 연결
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
	}
}

// InputMove -> 게임에서 수행하는 함수
// FInputActionValue를 값타입으로 바꿔서, MovementInput에 추가한다.
void ASXPlayerCharacter::InputMove(const FInputActionValue& InValue)
{
	FVector2D MovementVector = InValue.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MovementVector.X);
	AddMovementInput(GetActorRightVector(), MovementVector.Y);
}
