// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpPad.generated.h"

UCLASS()
class TPSHOOTER_API AJumpPad : public AActor
{
	GENERATED_BODY()
	
public:
	AJumpPad();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PadMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	
	class UBoxComponent* LaunchTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Pad")
	float UpForce = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Pad")
	float ForwardForce = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Pad")
	float Cooldown = 0.35f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Pad")
	bool bOnlyPlayer = true;

	float LastLaunchTime = -100.0f;

	UFUNCTION()
	void OnLaunchTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
