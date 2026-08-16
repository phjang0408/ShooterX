// SXHealthPack.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SXHealthPack.generated.h"

class USceneComponent;
class UBoxComponent;
class UStaticMeshComponent;
//  전방선언 추가
class URotatingMovementComponent;

UCLASS()
class SHOOTERX_API ASXHealthPack : public AActor
{
	GENERATED_BODY()

public:
	ASXHealthPack();

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

	// Rotating Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "ShooterX|SXHealthPack")
	TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;

	UPROPERTY(EditAnywhere, Category = "ShooterX|SXHealthPack")
	float RotationSpeed = 300.f;
};
