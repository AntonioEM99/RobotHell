// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPShooterGameMode.h"

ATPShooterGameMode::ATPShooterGameMode()
{
	// stub
}

void ATPShooterGameMode::BeginPlay()
{
	Super::BeginPlay();
	player = Cast<ATPShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyAI::StaticClass(), enemyArray);

	for(AActor* temp : enemyArray)
	{
		Cast<AEnemyAI>(temp)->StartbehaviorTree(player);
	}
}
