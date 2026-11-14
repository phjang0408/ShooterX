// SXCharacterBase.cpp

#include "Character/SXCharacterBase.h"
#include "Animation/SXAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"

ASXCharacterBase::ASXCharacterBase()
{
}

void ASXCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	USXAnimInstance* AnimInstance = Cast<USXAnimInstance>(GetMesh()->GetAnimInstance());
	if (IsValid(AnimInstance) == true)
	{
		AnimInstance->OnCheckHit.AddDynamic(this, &ThisClass::HandleOnCheckHit);
	}
}

void ASXCharacterBase::HandleOnCheckHit()
{
	UKismetSystemLibrary::PrintString(this, TEXT("HandleOnCheckHit"));
}
