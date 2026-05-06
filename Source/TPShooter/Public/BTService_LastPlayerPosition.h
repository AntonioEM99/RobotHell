// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "EnemyAI.h"
#include "BTService_LastPlayerPosition.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API UBTService_LastPlayerPosition : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_LastPlayerPosition();
	virtual void TickNode(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds) override;
	
};
