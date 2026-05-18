// Fill out your copyright notice in the Description page of Project Settings.


#include "Move.h"

// Sets default values for this component's properties
UMove::UMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMove::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	SetShouldMove(false);

	// ...
	
}


// Called every frame
void UMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector currentLocation = GetOwner()->GetActorLocation();
	reachTarget = currentLocation.Equals(targetlocation);

	if (!reachTarget)
	{
		float speed = moveOffset.Length() / moveTime;
		FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetlocation, DeltaTime, speed);
		GetOwner()->SetActorLocation(newLocation);
	}

}

void UMove::SetShouldMove(bool move)
{
	shouldMove = move;
	if (shouldMove)
	{
		targetlocation = StartLocation + moveOffset;
	}
	else
	{
		targetlocation = StartLocation;
	}
}

bool UMove::GetShouldMove() const
{
	return false;
}

