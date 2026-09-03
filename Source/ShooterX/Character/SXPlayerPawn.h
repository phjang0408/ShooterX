// SXPlayerPawn.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SXPlayerPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UFloatingPawnMovement;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SHOOTERX_API ASXPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ASXPlayerPawn();

protected:
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(EditDefaultsOnly, Category = "ShooterX|ASXPlayerPawn")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditDefaultsOnly, Category = "ShooterX|ASXPlayerPawn")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "ShooterX|ASXPlayerPawn")
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

	UPROPERTY(EditDefaultsOnly, Category = "ShooterX|ASXPlayerPawn")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, Category = "ShooterX|ASXPlayerPawn")
	TObjectPtr<UCameraComponent> CameraComponent;

	// Input Components function
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// 바인드 될 호출함수
	void GOFrontRear(float InAxisValue);
	
	void GOLeftRight(float InAxisValue);
};
