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