// SXAnimInstance.h

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SXAnimInstance.generated.h"

class ASXCharacterBase;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class SHOOTERX_API USXAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// AnimInstance에서의 BeginPlay()함수 : NativeInitializeAnimation()
	virtual void NativeInitializeAnimation() override;

	// Anim에서의 Tick()함수 : NativeUpdateAnimation()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
	TObjectPtr<ASXCharacterBase> OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly)
	TObjectPtr<UCharacterMovementComponent> OwnerCharacterMovement;

#pragma region Walk
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector Velocity;	// 속도 벡터

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float GroundSpeed;	// z

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 bShouldMove : 1;	// bool, 
#pragma endregion
};
