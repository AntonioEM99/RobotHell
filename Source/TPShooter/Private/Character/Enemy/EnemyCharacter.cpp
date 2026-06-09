// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	// Esto hace que la IA posea al enemigo aunque sea spawneado o activado desde un pool
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// Configuramos la IA para que pueda rotar hacia el jugador
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
    
	// Podemos ajustar una velocidad diferente a la del jugador
	GetCharacterMovement()->MaxWalkSpeed = 300.f; 
}

void AEnemyCharacter::BeginPlay()
{
	// Super llama a AATPCharacterBase::BeginPlay(), que spawnea el arma
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Enemy spawned"));

	if (GetController())
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller: %s"), *GetController()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO CONTROLLER"));
	}
}
