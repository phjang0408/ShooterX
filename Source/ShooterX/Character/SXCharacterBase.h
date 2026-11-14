// SXCharacterBase.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SXCharacterBase.generated.h"

class UAnimMontage;

UCLASS()
class SHOOTERX_API ASXCharacterBase : public ACharacter
{
	GENERATED_BODY()

#pragma region Override ACharacter
public:
	ASXCharacterBase();

protected:
	virtual void BeginPlay() override;
#pragma endregion

#pragma region Attack

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMeleeMontage;

	UFUNCTION()
	void HandleOnCheckHit();
#pragma endregion

};
