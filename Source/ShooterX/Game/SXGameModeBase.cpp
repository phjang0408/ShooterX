// SXGameModeBase.cpp

#include "Game/SXGameModeBase.h"
#include "Player/SXPlayerController.h"
#include "Character/SXPlayerPawn.h"

ASXGameModeBase::ASXGameModeBase()
{
	// 객체를 생성하는 것이 아닌, 플레이어 컨트롤러 클래스 정보를 지정해줌.
	// GameModeBase의 PlayerControllerClass 속성을 SXPlayerController로 지정하는 코드

	// 멀티플레이까지 고려한 구조, 플레이어 입장 시 플레이어 컨트롤러를 생성.
	// 이는 PlayerCharacter, PlayerStateClass도 마찬가지
	PlayerControllerClass = ASXPlayerController::StaticClass();

	// 마찬가지로 PlayerPawn도 지정
	DefaultPawnClass = ASXPlayerPawn::StaticClass();
}

void ASXGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	UE_LOG(LogTemp, Error, TEXT("         Start ASXGameModeBase::     InitGame()"));
	Super::InitGame(MapName, Options, ErrorMessage);
	UE_LOG(LogTemp, Error, TEXT("         End   ASXGameModeBase::     InitGame()"));
}

void ASXGameModeBase::InitGameState()
{
	UE_LOG(LogTemp, Error, TEXT("         Start ASXGameModeBase::     InitGameState()"));
	Super::InitGameState();
	UE_LOG(LogTemp, Error, TEXT("         End   ASXGameModeBase::     InitGameState()"));
}

void ASXGameModeBase::PostInitializeComponents()
{
	UE_LOG(LogTemp, Error, TEXT("         Start ASXGameModeBase::     PostInitializeComponents()"));
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Error, TEXT("         End   ASXGameModeBase::     PostInitializeComponents()"));
}

void ASXGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	UE_LOG(LogTemp, Error, TEXT("         Start ASXGameModeBase::     PreLogin()"));
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	UE_LOG(LogTemp, Error, TEXT("         End   ASXGameModeBase::     PreLogin()"));
}

APlayerController* ASXGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl UniqueId, FString& ErrorMessage)
{
	UE_LOG(LogTemp, Error, TEXT("         Start ASXGameModeBase::     Login()"));
	APlayerController* PlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	UE_LOG(LogTemp, Error, TEXT("         End   ASXGameModeBase::     Login()"));

	return PlayerController;
}

void ASXGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Error, TEXT("         Start ASXGameModeBase::     PostLogin(ASXPlayerController)"));
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Error, TEXT("         End   ASXGameModeBase::     PostLogin(ASXPlayerController)"));
}
