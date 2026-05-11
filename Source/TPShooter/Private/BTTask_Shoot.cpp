// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "EnhancedInput/Public/InputActionValue.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& root, uint8* NodeMemory)
{
	Super::ExecuteTask(root, NodeMemory);

	AEnemyAI* controller = Cast<AEnemyAI>(root.GetAIOwner());
	ATPShooterCharacter* myCharacter = controller->getMyCharacter();

	if(controller->getPlayerCharacter()->isAlive)
	{
		myCharacter->Shoot();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
