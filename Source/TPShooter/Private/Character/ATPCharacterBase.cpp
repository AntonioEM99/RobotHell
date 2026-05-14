#include "Character/ATPCharacterBase.h"
#include "Components/CapsuleComponent.h"

AATPCharacterBase::AATPCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	health = maxHealth;
}

void AATPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
    
	health = maxHealth;
	OnTakeAnyDamage.AddDynamic(this, &AATPCharacterBase::OnDamageTaken);

	// Spawn del arma (lo que tenías en el player)
	if (gunClass)
	{
		currentGun = GetWorld()->SpawnActor<AGun>(gunClass);
		if (currentGun)
		{
			currentGun->SetOwner(this);
			currentGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));
			currentGun->ownerController = GetController();
		}
	}
}

void AATPCharacterBase::Shoot()
{
	if (currentGun && isAlive) 
	{
		currentGun->PullTrigger();
	}
}

void AATPCharacterBase::OnDamageTaken(AActor* damagedActor, float Damage, const UDamageType* DamageType, AController* instigatedBy, AActor* DamageCauser)
{
	if (isAlive)
	{
		health -= Damage;
		if (health <= 0)
		{
			isAlive = false;
			health = 0;
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			// Aquí puedes añadir una animación de muerte después
		}
	}
}