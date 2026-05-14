// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyBTTask_clearBB.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API UMyBTTask_clearBB : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_clearBB();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* NodeMemory) override;
	
};
