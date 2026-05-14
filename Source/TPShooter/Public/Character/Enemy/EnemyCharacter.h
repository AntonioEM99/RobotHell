// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ATPCharacterBase.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API AEnemyCharacter : public AATPCharacterBase
{
	GENERATED_BODY()
public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

	// Aquí podrías añadir lógica para cuando el enemigo muere (ej. soltar loot)
};
