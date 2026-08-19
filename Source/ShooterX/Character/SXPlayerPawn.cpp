// SXPlayerPawn.cpp


#include "Character/SXPlayerPawn.h"

ASXPlayerPawn::ASXPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASXPlayerPawn::PostInitializeComponents()
{
	UE_LOG(LogTemp, Log, TEXT("                Start ASXPlayerPawn::      PostInitializeComponents()"));
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Log, TEXT("                End   ASXPlayerPawn::      PostInitializeComponents()"));
}

void ASXPlayerPawn::PossessedBy(AController* NewController)
{
	UE_LOG(LogTemp, Log, TEXT("                Start ASXPlayerPawn::      PossessedBy(ASXPlayerController)"));
	Super::PossessedBy(NewController);
	UE_LOG(LogTemp, Log, TEXT("                End   ASXPlayerPawn::      PossessedBy(ASXPlayerController)"));
}

void ASXPlayerPawn::UnPossessed()
{
	UE_LOG(LogTemp, Log, TEXT("                Start ASXPlayerPawn::      UnPossessed()"));
	Super::UnPossessed();
	UE_LOG(LogTemp, Log, TEXT("                End   ASXPlayerPawn::      UnPossessed()"));
}

void ASXPlayerPawn::Tick(float DeltaSeconds)
{
	// 원래는 Tick이므로, 매 Tick마다 호출됨.
	// 지금은 한 번만 찍어보려고, bOnce를 정의해서 보려는것임
	static bool bOnce = false;
	if (false == bOnce)
	{
		UE_LOG(LogTemp, Log, TEXT("                Start ASXPlayerPawn::      Tick()"));
	}
	Super::Tick(DeltaSeconds);
	if (false == bOnce)
	{
		UE_LOG(LogTemp, Log, TEXT("                End   ASXPlayerPawn::      Tick()"));
		bOnce = true;
	}
}

void ASXPlayerPawn::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogTemp, Log, TEXT("                Start ASXPlayerPawn::      EndPlay()"));
	Super::EndPlay(EndPlayReason);
	UE_LOG(LogTemp, Log, TEXT("                End   ASXPlayerPawn::      EndPlay()"));
}

void ASXPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Log, TEXT("                Start ASXPlayerPawn::      SetupPlayerInputComponent(PlayerInputComponent)"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UE_LOG(LogTemp, Log, TEXT("                End   ASXPlayerPawn::      SetupPlayerInputComponent(PlayerInputComponent)"));
}

void ASXPlayerPawn::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("                Start ASXPlayerPawn::      BeginPlay()"));
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("                End   ASXPlayerPawn::      BeginPlay()"));
}
