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
	if(enemyTree)
	{
		myCharacter = Cast<ATPShooterCharacter>(GetPawn());
		PlayerPawn = character;

		RunBehaviorTree(enemyTree);
		if(myCharacter || PlayerPawn)
		{
			UBlackboardComponent* blackboard = GetBlackboardComponent();
			if (blackboard)
			{

				GetBlackboardComponent()->SetValueAsVector("StartLocation", myCharacter->GetActorLocation());
				GetBlackboardComponent()->SetValueAsVector("PlayerLocation", PlayerPawn->GetActorLocation());
			}
		}
	}
}
