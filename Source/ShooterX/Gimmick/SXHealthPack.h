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

	// 이벤트 함수
	// AActor에서 override하여 사용한다.
	// 여기선, 힐팩의 위치를 BeginPlay로 구하고, 매 틱마다 상하로 움직이는 기능을 구현한다.
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Meta = (AllowPrivateAccess),  Category = "ShooterX|SXHealthPack")
	float HealAmount;

	uint8 bIsUsed : 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess), Category = "ShooterX|SXHealthPack");
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess), Category = "ShooterX|SXHealthPack");
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess), Category = "ShooterX|SXHealthPack");
	TObjectPtr<UStaticMeshComponent> BodyStaticMeshComponent;

	// 이벤트 함수
	// 
	FVector StartLocation;

	float ElapsedTime = 0.f;	// 몇 초가 경과되었는지 

	// Sin함수 쓸 거라, 진폭(움직이는 범위)과 속도(움직이는 속도)를 설정
	UPROPERTY(EditAnywhere, Category = "ShooterX|SXHealthPack")
	float Amplitude = 10.f;

	UPROPERTY(EditAnywhere, Category = "ShooterX|SXHealthPack")
	float MovementSpeed = 2.f;
};
