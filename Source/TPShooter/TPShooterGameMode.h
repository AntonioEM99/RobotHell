// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TPShooterCharacter.h"
#include "EnemyAI.h"
#include "TPShooterGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class ATPShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Constructor */
	ATPShooterGameMode();

protected:
	virtual void BeginPlay() override;
	

	ATPShooterCharacter* player;
	TArray<AActor*> enemyArray;
};



