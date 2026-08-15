// SXHealthPack.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SXHealthPack.generated.h"

class USceneComponent;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class SHOOTERX_API ASXHealthPack : public AActor
{
	GENERATED_BODY()

public:
	ASXHealthPack();

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess),  Category = "ShooterX|SXHealthPack")
	float HealAmount;

	// bool bIsUsed
	uint8 bIsUsed : 1;


	// 컴포넌트 생성 시, '컴포지션(Has-A)'관계로 생성한다 하였다.
	// 이를 위해, '값'형식 컴포넌트를, 프로퍼티에 생성한다.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess), Category = "ShooterX|SXHealthPack");
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess), Category = "ShooterX|SXHealthPack");
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess), Category = "ShooterX|SXHealthPack");
	TObjectPtr<UStaticMeshComponent> BodyStaticMeshComponent;
};
