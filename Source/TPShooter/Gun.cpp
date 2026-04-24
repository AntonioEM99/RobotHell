// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root"));
	SetRootComponent(rootComp);

	skeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	skeletalMeshComp->SetupAttachment(rootComp);
}

void AGun::PullTrigger()
{
	
	if (ownerController) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Disparo"));
		FVector viewPointLocation;
		FRotator viewPointRotation;
		ownerController->GetPlayerViewPoint(viewPointLocation, viewPointRotation);
		//Debug de camara
		//DrawDebugCamera(GetWorld(), viewPointLocation, viewPointRotation, 90, 2, FColor::Red, true);
		//Raycast
		FVector endPoint = viewPointLocation + (viewPointRotation.Vector() * maxRange);
		FHitResult hit;
		FCollisionQueryParams params;
		params.AddIgnoredActor(GetOwner());
		params.AddIgnoredActor(this);
		bool isHit = GetWorld()->LineTraceSingleByChannel(hit, viewPointLocation, endPoint, ECC_GameTraceChannel2, params);

		if (isHit) 
		{
			DrawDebugSphere(GetWorld(), hit.ImpactPoint, 5, 8, FColor::Yellow, true);
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

