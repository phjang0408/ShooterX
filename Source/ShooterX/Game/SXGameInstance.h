// SXGameInstance.h

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SXGameInstance.generated.h"

class USXPigeon;
	// 전방 선언!
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

	// 콜백 함수 등록 => Dynamic이므로 꼭 UFUNCION을 적어줘야 함.
	UFUNCTION()
	void HandlePigeonFlying(const FString& InName, const int32 InID);

protected:
	UPROPERTY()
	FString Name;

	// 새로운 UObject 포인터 프로터피 선언
	UPROPERTY()
	TObjectPtr<USXPigeon> SpawnedPigeon;

};
