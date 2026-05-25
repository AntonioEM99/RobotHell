// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TPSHOOTER_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "UI")
	UProgressBar* HealthBar;

	UFUNCTION(BlueprintCallable)
	void SetPorcent(float value);
	
};
