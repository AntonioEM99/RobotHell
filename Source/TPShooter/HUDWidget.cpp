// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

void UHUDWidget::SetPorcent(float value)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(FMath::Clamp(value, 0.0f, 1.0f));
	}
}
