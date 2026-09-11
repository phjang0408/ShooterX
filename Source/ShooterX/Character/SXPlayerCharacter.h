// SXPlayerCharacter.h
#pragma once

#include "CoreMinimal.h"
#include "Character/SXCharacterBase.h"
#include "InputActionValue.h"
#include "SXPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USXInputConfig;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class SHOOTERX_API ASXPlayerCharacter : public ASXCharacterBase
{
	GENERATED_BODY()
	
#pragma region Override ACharacter

public:
	ASXPlayerCharacter();

	virtual void BeginPlay() override;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> CameraComponent;

#pragma endregion

#pragma region Input
private:
	void InputMove(const FInputActionValue& InValue);
	
	void InputLook(const FInputActionValue& InValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USXInputConfig> PlayerCharacterInputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPriavteAccess))
	TObjectPtr<UInputMappingContext> PlayerCharacterInputMappingContext;
	
#pragma endregion
};
