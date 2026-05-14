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

	// El enemigo no necesita ocultar huesos específicos ni actualizar HUDs de jugador
	UE_LOG(LogTemp, Warning, TEXT("Enemigo spawneado con exito"));
}
