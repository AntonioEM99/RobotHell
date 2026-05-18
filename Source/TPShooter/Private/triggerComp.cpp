// Fill out your copyright notice in the Description page of Project Settings.


#include "triggerComp.h"

UtriggerComp::UtriggerComp()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UtriggerComp::BeginPlay()
{
	Super::BeginPlay();
	if(moveActor)
	{
		moveComponent = moveActor->FindComponentByClass<UMove>();
	}
	if(IsPreshurePlate)
	{
		OnComponentBeginOverlap.AddDynamic(this, &UtriggerComp::OnOverlapBegin);
		OnComponentEndOverlap.AddDynamic(this, &UtriggerComp::OnOverlapEnd);
	}

}

void UtriggerComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UtriggerComp::trigger(bool triggerValue)
{
	isTriggered = triggerValue;
	if(moveComponent)
	{
		moveComponent->SetShouldMove(isTriggered);
	}
}

void UtriggerComp::OnOverlapBegin(UPrimitiveComponent* verlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(otherActor && otherActor->ActorHasTag("Player"))
	{
		if (!isTriggered)
		{
			trigger(true);
		}
	}
}

void UtriggerComp::OnOverlapEnd(UPrimitiveComponent* verlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	if (otherActor && otherActor->ActorHasTag("Player"))
	{
		if (isTriggered)
		{
			trigger(false);
		}
	}
}
