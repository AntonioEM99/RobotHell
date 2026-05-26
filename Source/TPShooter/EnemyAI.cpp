// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//MoveToActor(PlayerPawn);
}

void AEnemyAI::StartbehaviorTree(ATPShooterCharacter* character)
{
	if (enemyTree)
	{
		myCharacter = Cast<ATPShooterCharacter>(GetPawn());
		PlayerPawn = character;

		if (myCharacter && PlayerPawn)
		{
			RunBehaviorTree(enemyTree);

			UBlackboardComponent* blackboard = GetBlackboardComponent();

			if (blackboard)
			{
				blackboard->SetValueAsVector("StartLocation", myCharacter->GetActorLocation());
				blackboard->SetValueAsVector("PlayerLocation", PlayerPawn->GetActorLocation());
			}
		}
	}
}
