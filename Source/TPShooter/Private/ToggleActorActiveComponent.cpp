// Fill out your copyright notice in the Description page of Project Settings.


#include "ToggleActorActiveComponent.h"

// Sets default values for this component's properties
UToggleActorActiveComponent::UToggleActorActiveComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	actor = GetOwner();
}

void UToggleActorActiveComponent::SetActorActive(bool active)
{
	if (actor == nullptr)
	{
		return;
	}

	actor->SetActorHiddenInGame(!active);
	actor->SetActorTickEnabled(active);
	actor->SetActorEnableCollision(active);
}

// Called when the game starts
void UToggleActorActiveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



