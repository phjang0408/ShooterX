// SXWeapon.cpp

#include "Item/Weapon/SXWeapon.h"
#include "Item/Weapon/Component/SXPickupComponent.h"
#include "Character/SXPlayerCharacter.h"

ASXWeapon::ASXWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupComponent = CreateDefaultSubobject<USXPickupComponent>(TEXT("PickupComponent"));
	SetRootComponent(PickupComponent);
}

void ASXWeapon::BeginPlay()
{
	Super::BeginPlay();

	PickupComponent->OnPickUp.AddDynamic(this, &ThisClass::HandleOnPickUp);
}

void ASXWeapon::HandleOnPickUp(ASXPlayerCharacter* InPickUpCharacter)
{
	// UE_LOG(LogTemp, Error, TEXT("HandleOnPickUp(%s)"), *InPickUpCharacter->GetName());

	if (IsValid(InPickUpCharacter) == false) { return; }

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	// 캐릭터 메시에 hand_rSocket를 찾아서, AttachmentRules에 따라 붙임.
	AttachToComponent(InPickUpCharacter->GetMesh(), AttachmentRules, FName(TEXT("hand_rSocket")));	
	
	// Weapon의 Collision Enable
	SetActorEnableCollision(false);
	// Weapon의 RootComponent였던 PickupComponent의 물리 해제, 부착된 손의 Physic를 따라감.
	PickupComponent->SetSimulatePhysics(false);
}
