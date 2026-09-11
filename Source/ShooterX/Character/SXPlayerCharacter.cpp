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
	FRotator PivotRotation(0.f, -90.f, 0.f);
	GetMesh()->SetRelativeLocationAndRotation(PivotPosition, PivotRotation);

	// 3. SpringArm-Camera 컴포넌트 생성
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->SetRelativeLocation(FVector(0.f, 50.f, 100.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	// 4. 속도, 점프 높이 설정
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->JumpZVelocity = 700.f;
	// GetCharacterMovement()->bOrientRotationToMovement = true; : 이동방향으로 카메라가 따라가도록하는 설정
	// GetCharacterMovement()->MaxAcceleration = 2000.f; : 초기 가속도 설정
	// GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; : 입력을 뗐을 때 얼마나 빨리 멈추는지
	// AirControl, .bCanCrouch, CrouchedHalfHeight 등이 있다.
	
	// [속성 설정]
	bUseControllerRotationPitch = false; // 위아래, true면, 몸 전체가 움직일거라 false로, 다만 카메라는 true
	bUseControllerRotationRoll = false; // 갸우뚱, X
	bUseControllerRotationYaw = true;	// 좌우, false면 좌우 회전 시 Pawn이 따라오지 않게 할 수 있음.

	SpringArmComponent->bUsePawnControlRotation = true;	// 명시적(Controller에서 True라서)으로 적은

	SpringArmComponent->bInheritPitch = true;	// Pawn은 안 움직이지만, Camera는 움직여야함.
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = true;

	SpringArmComponent->bDoCollisionTest = true;	// 카메라사이 벽

	// CharacterMovement Components
	// GetCharacterMovement()->RotationRate = FRotator(0.f, 20.f, 0.f);
	// GetCharacterMovement()->bUseControllerDesiredRotation = false;	// bUseControllerRotationYaw가 False여야 의미가 있음.
	// GetCharacterMovement()->bOrientRotationToMovement = false;	
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

	// 1. 엔진이 준비한 UInputComponent를 EnhancedInputComponent로 Cast
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent) == true)
	{	// 2. BindAction함수를 통해, "Move IA가 Triggered로 발생하면, this에서 InputMove 함수를 실행한다."로 연결
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::InputMove);
		EnhancedInputComponent->BindAction(PlayerCharacterInputConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::InputLook);
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

void ASXPlayerCharacter::InputLook(const FInputActionValue& InValue)
{
	FVector2D LookVector = InValue.Get<FVector2D>();

	// 마우스 감도를 조절하려면, LookVector에 계수를 곱하면서 감도 조절
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}
