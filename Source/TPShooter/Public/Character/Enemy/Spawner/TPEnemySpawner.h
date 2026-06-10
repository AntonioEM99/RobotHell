// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPEnemySpawner.generated.h"

class UBoxComponent;
class AATPCharacterBase;

UCLASS()
class TPSHOOTER_API ATPEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ATPEnemySpawner();

protected:
	virtual void BeginPlay() override;

	// Función para el temporizador
	void TickSpawn();

	// Saca un enemigo de la "piscina"
	void GetEnemyFromPool();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* SpawnArea;

	/** Configuración del Pool */
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<AATPCharacterBase> EnemyClass;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	int32 PoolSize = 5;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	float SpawnInterval = 3.0f;

private:
	// Nuestra lista de enemigos reutilizables
	UPROPERTY()
	TArray<AATPCharacterBase*> EnemyPool;

	FTimerHandle SpawnTimerHandle;
};