#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SXUnrealObject.generated.h"

UCLASS()
class SHOOTERX_API USXUnrealObject : public UObject {
	GENERATED_BODY()

public:
	USXUnrealObject();

	UFUNCTION()
	void HelloUnreal();

	const FString& GetObjectName() const { return Name; }

protected:
	UPROPERTY()
	FString Name;
};