// SXGameModeBase.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SXgameModeBase.generated.h"

UCLASS()
class SHOOTERX_API ASXGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASXGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void InitGameState() override;

	virtual void PostInitializeComponents() override;

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl UniqueId, FString& ErrorMessage);

	virtual void PostLogin(APlayerController* NewPlayer) override;

};