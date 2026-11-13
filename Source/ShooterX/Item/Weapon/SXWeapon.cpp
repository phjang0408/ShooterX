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
	AttachToComponent(InPickUpCharacter->GetMesh(), AttachmentRules, FName(TEXT("hand_rSocket")));	
	SetActorEnableCollision(false);
	PickupComponent->SetSimulatePhysics(false);
}
