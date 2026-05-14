// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_clearBB.h"

UMyBTTask_clearBB::UMyBTTask_clearBB()
{
	NodeName = TEXT("Clear Value");
}

EBTNodeResult::Type UMyBTTask_clearBB::ExecuteTask(UBehaviorTreeComponent& root, uint8* NodeMemory)
{
	Super::ExecuteTask(root, NodeMemory);

	UBlackboardComponent* bb = root.GetBlackboardComponent();
	bb->ClearValue(GetSelectedBlackboardKey());
	return EBTNodeResult::Succeeded;
}
