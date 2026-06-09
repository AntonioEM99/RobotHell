#include "Character/ATPCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "TPShooterCharacter.h"

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
	if (!isAlive || !currentGun)
	{
		return;
	}

	currentGun->SetOwner(this);
	currentGun->ownerController = GetController();
	currentGun->PullTrigger();
}

void AATPCharacterBase::OnDamageTaken(AActor* damagedActor, float Damage, const UDamageType* DamageType, AController* instigatedBy, AActor* DamageCauser)
{
	if (isAlive)
	{
		health -= Damage;
		health = FMath::Clamp(health, 0.0f, maxHealth);

		if (health <= 0)
		{
			isAlive = false;
			health = 0;
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			APlayerController* shake = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			shake->ClientStartCameraShake(cameraShake);
		}

		if (ATPShooterCharacter* player = Cast<ATPShooterCharacter>(this))
		{
			if (player->IsPlayerControlled())
			{
				player->UpdateHUD();
			}
		}
	}
}