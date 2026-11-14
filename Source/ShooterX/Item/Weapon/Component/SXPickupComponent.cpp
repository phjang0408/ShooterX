// SXPickupComponent.cpp

#include "Item/Weapon/Component/SXPickupComponent.h"
#include "Character/SXPlayerCharacter.h"

USXPickupComponent::USXPickupComponent()
{	
	PrimaryComponentTick.bCanEverTick = false;
}

void USXPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	// UPrimitiveComponent에 선언된 
	// 겹치게 되면, 등록된 Delegate함수를 실행한다.
	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HandleOnComponentBeginOverlap);
}

void USXPickupComponent::HandleOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASXPlayerCharacter* OverlappedCharacter = Cast<ASXPlayerCharacter>(OtherActor);
	if (IsValid(OverlappedCharacter) == true)
	{
		// 겹친 캐릭터도 같이 인자로 전송
		OnPickUp.Broadcast(OverlappedCharacter);

		// AddDyanmic 정리
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
