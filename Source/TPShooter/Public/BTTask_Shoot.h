// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyAI.h"
#include "BTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API UBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_Shoot();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& root, uint8* NodeMemory) override;
	
};
