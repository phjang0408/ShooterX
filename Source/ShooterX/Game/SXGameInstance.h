// SXGameInstance.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SXGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERX_API USXGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USXGameInstance();	// 헤더에서 바로 생성자 구체정의 단축키 : alt + enter

	virtual void Init() override;

	virtual void Shutdown() override;

};
