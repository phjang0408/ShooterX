// SXPickupComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SXPickupComponent.generated.h"

class ASXPlayerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, ASXPlayerCharacter*, InPickUpCharacter);
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERX_API USXPickupComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	USXPickupComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandleOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(BlueprintAssignable)
	FOnPickUp OnPickUp;
};
