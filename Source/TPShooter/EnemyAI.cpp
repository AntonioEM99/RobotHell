// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if(PlayerPawn)
	{
		SetFocus(PlayerPawn);
	}
}

void AEnemyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
