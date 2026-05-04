// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_LastPlayerPosition.h"

UBTService_LastPlayerPosition::UBTService_LastPlayerPosition()
{
	NodeName = TEXT("Upadte Last Known Player Position");
}

void UBTService_LastPlayerPosition::TickNode(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds)
{
	Super::TickNode(ownerComp, nodeMemory, deltaSeconds);
	AEnemyAI* controller = Cast<AEnemyAI>(ownerComp.GetAIOwner());
	ATPShooterCharacter* player = controller->getPlayerCharacter();
	UBlackboardComponent* blackboard = controller->GetBlackboardComponent();

	if (player)
	{
		blackboard->SetValueAsVector("LastKnownLocation", player->GetActorLocation());
	}

}
