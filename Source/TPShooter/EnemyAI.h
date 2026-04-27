// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API AEnemyAI : public AAIController
{
	GENERATED_BODY()

	protected:
		APawn* PlayerPawn;
		virtual void BeginPlay() override;

		virtual void Tick(float DeltaSeconds) override;
	
};
