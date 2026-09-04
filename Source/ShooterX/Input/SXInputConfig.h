// SXInputConfig.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SXInputConfig.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class SHOOTERX_API USXInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> Move;
};
