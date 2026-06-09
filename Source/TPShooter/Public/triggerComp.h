// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Move.h"
#include "TPShooterCharacter.h"
#include "triggerComp.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TPSHOOTER_API UtriggerComp : public UBoxComponent
{
	GENERATED_BODY()

public:
	UtriggerComp();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void trigger(bool triggerValue);

	UPROPERTY(EditAnywhere)
	bool IsPreshurePlate = false;

	UPROPERTY(VisibleAnywhere)
	bool isTriggered = false;


	UPROPERTY(EditAnywhere) 
	bool IsMedKit = false; 

	UPROPERTY(EditAnywhere) 
	float medKits = 50.0f;


	UPROPERTY(EditAnywhere)
	AActor* moveActor;

	UMove* moveComponent;

	ATPShooterCharacter* player;


	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* verlappedComp, class AActor* otherActor, 
		UPrimitiveComponent* otherComp, int32 otherBodyIndex, 
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* verlappedComp, class AActor* otherActor, 
		UPrimitiveComponent* otherComp, int32 otherBodyIndex);
	
};
