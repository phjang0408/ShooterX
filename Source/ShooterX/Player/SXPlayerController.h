// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SXPlayerController.generated.h"

UCLASS()
class SHOOTERX_API ASXPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASXPlayerController();

	virtual void PostInitializeComponents() override;

	virtual void PlayerTick(float DeltaSeconds) override;

protected:
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* aPawn) override;

	virtual void OnUnPossess() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
};
