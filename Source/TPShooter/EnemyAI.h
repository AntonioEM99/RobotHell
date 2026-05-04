// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "TPShooterCharacter.h"
#include "BehaviorTree/blackboardComponent.h"
#include "EnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API AEnemyAI : public AAIController
{
	GENERATED_BODY()

	protected:
		ATPShooterCharacter* PlayerPawn;

		ATPShooterCharacter* myCharacter;

		UPROPERTY(EditAnywhere)
		UBehaviorTree* enemyTree;

		virtual void BeginPlay() override;

		virtual void Tick(float DeltaSeconds) override;


public:
	void StartbehaviorTree(ATPShooterCharacter* character);
	
	ATPShooterCharacter* getPlayerCharacter() const { return PlayerPawn; };
	ATPShooterCharacter* getMyCharacter() const { return myCharacter; };
};
