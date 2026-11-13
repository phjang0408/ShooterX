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
	UE_LOG(LogTemp, Error, TEXT("HandleOnPickUp(%s)"), *InPickUpCharacter->GetName());
}
