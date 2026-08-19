// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SXPlayerPawn.generated.h"

UCLASS()
class SHOOTERX_API ASXPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ASXPlayerPawn();

	virtual void PostInitializeComponents() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;
};
