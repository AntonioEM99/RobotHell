// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("Update Player Location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds)
{
	Super::TickNode(ownerComp, nodeMemory, deltaSeconds);
	AEnemyAI* controller = Cast<AEnemyAI>(ownerComp.GetAIOwner());
	ATPShooterCharacter* player = controller->getPlayerCharacter();
	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();

	if (controller->LineOfSightTo(player))
	{
		controller->SetFocus(player);
		blackboard->SetValueAsVector(GetSelectedBlackboardKey(), player->GetActorLocation());
	}
	else
	{
		controller->ClearFocus(EAIFocusPriority::Gameplay);
		blackboard->ClearValue(GetSelectedBlackboardKey());
	}
	
}
