// SXPlayerController.cpp

#include "Player/SXPlayerController.h"

ASXPlayerController::ASXPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASXPlayerController::PostInitializeComponents()
{
	UE_LOG(LogTemp, Warning, TEXT("       Start ASXPlayerController::PostInitializeComponents()"));
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Warning, TEXT("       End ASXPlayerController::PostInitializeComponents()"));
}

void ASXPlayerController::PlayerTick(float DeltaSeconds)
{
	// 원래는 Tick이므로, 매 Tick마다 호출됨.
	// 지금은 한 번만 찍어보려고, bOnce를 정의해서 보려는것임
	static bool bOnce = false;
	if (false == bOnce)
	{
		UE_LOG(LogTemp, Warning, TEXT("       Start ASXPlayerController::PlayerTick()"));
	}
	Super::PlayerTick(DeltaSeconds);
	if (false == bOnce)
	{
		UE_LOG(LogTemp, Warning, TEXT("       End ASXPlayerController::PlayerTick()"));
		bOnce = true;
	}
}

void ASXPlayerController::SetupInputComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("       Start ASXPlayerController::SetupInputCOmponent()"));
	Super::SetupInputComponent();
	UE_LOG(LogTemp, Warning, TEXT("       End ASXPlayerController::SetupInputComponent()"));
}

void ASXPlayerController::OnPossess(APawn* aPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("       Start ASXPlayerController::OnPossess()"));
	Super::OnPossess(aPawn);
	UE_LOG(LogTemp, Warning, TEXT("       End ASXPlayerController::OnPOssess()"));
}

void ASXPlayerController::OnUnPossess()
{
	UE_LOG(LogTemp, Warning, TEXT("       Start ASXPlayerController::OnUnPossess()"));
	Super::OnUnPossess();
	UE_LOG(LogTemp, Warning, TEXT("       End   ASXPlayerController::OnUnPossess()"));
}

void ASXPlayerController::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("       Start ASXPlayerController::BeginPlay()"));
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("       End   ASXPlayerController::BeginPlay()"));
}

void ASXPlayerController::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	// Super::EndPlay는 내가 쓴 로직뒤, 즉 제일 마지막에!
	// Super함수가 마무리, 정리, 종료의 느낌이면, 내 로직뒤에 작성해야 함.
	UE_LOG(LogTemp, Warning, TEXT("       Start ASXPlayerController::EndPlay()"));
	Super::EndPlay(EndPlayReason);
	UE_LOG(LogTemp, Warning, TEXT("       End   ASXPlayerController::EndPlay()"));
}
