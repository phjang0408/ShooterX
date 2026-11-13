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

	// this Component에 Delegate가 발생하면 실행되는 Dyanimc을 추가한다.
	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::HandleOnComponentBeginOverlap);
}

void USXPickupComponent::HandleOnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASXPlayerCharacter* OverlappedCharacter = Cast<ASXPlayerCharacter>(OtherActor);
	if (IsValid(OverlappedCharacter) == true)
	{
		OnPickUp.Broadcast(OverlappedCharacter);

		// AddDyanmic 정리
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
