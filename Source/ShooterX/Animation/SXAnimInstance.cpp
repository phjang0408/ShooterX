// SXAnimInstance.cpp

#include "Animation/SXAnimInstance.h"
#include "Character/SXCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USXAnimInstance::NativeInitializeAnimation()
{
	// Character -> Skeletal Mesh -> AnimInstance로 내려가는데,
	// Anim에서 Character(OwnerPawn)을 접근하려면 "TryGetPawnOnwer"를 사용한다.
	APawn* OwnerPawn = TryGetPawnOwner();
	if (IsValid(OwnerPawn) == true)
	{
		OwnerCharacter = Cast<ASXCharacterBase>(OwnerPawn);
		if ((IsValid(OwnerCharacter) == true))
		{
			OwnerCharacterMovement = OwnerCharacter->GetCharacterMovement();

		}
		// 상위->하위에 접근하려면, Charcter -> AnimInstance면, Get...
		// 하위->상위에 접근하려면, AnimInstance -> Character면, TryGet...

		// 상하위는 언리얼의 생명주기(Input -> Game Logic -> Anim -> ...)를 따름.
	}
}

void USXAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (IsValid(OwnerCharacterMovement) == true)
	{
		Velocity = OwnerCharacterMovement->Velocity;
		GroundSpeed = UKismetMathLibrary::VSizeXY(Velocity); // vector의 크기를 speed로 설정

		// float에서 0을 판멸하는 법 : IsNearlyZero() or KINDA_SMALL_NUMBER와 비교
		// 현재 속도가 0 && 가속도도 0이면 멈춘다고 판별
		float GroundAcceleration = UKismetMathLibrary::VSizeXY(OwnerCharacterMovement->GetCurrentAcceleration());
		bool bIsAccelerationNearZero = FMath::IsNearlyZero(GroundAcceleration);

		bShouldMove = (KINDA_SMALL_NUMBER < GroundSpeed) && (bIsAccelerationNearZero == false);
	}
}
