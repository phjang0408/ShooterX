// SXWeapon.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SXWeapon.generated.h"

class ASXPlayerCharacter;
class USXPickupComponent;

UCLASS()
class SHOOTERX_API ASXWeapon : public AActor
{
	GENERATED_BODY()

public:
	ASXWeapon();

	FORCEINLINE USXPickupComponent* GetPickupComponent() const { return PickupComponent; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleOnPickUp(ASXPlayerCharacter* InPickUpCharacter);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USXPickupComponent> PickupComponent;
};