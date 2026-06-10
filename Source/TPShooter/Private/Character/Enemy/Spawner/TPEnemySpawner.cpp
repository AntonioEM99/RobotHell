// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/Spawner/TPEnemySpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h" 
#include "Character/ATPCharacterBase.h"

ATPEnemySpawner::ATPEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	SpawnArea = CreateDefaultSubobject<UBoxComponent>("SpawnArea");
	SpawnArea->SetupAttachment(RootComponent);
}

void ATPEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!EnemyClass) return;

	// 1. Llenamos el Pool al inicio
	for (int32 i = 0; i < PoolSize; i++)
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		AATPCharacterBase* PooledEnemy = GetWorld()->SpawnActor<AATPCharacterBase>(EnemyClass, FVector::ZeroVector, FRotator::ZeroRotator, Params);
		
		if (PooledEnemy)
		{
			// Forzamos la creación del AI Controller
			PooledEnemy->SpawnDefaultController();

			UE_LOG(
				LogTemp,
				Warning,
				TEXT("Controller = %s"),
				PooledEnemy->GetController()
				? *PooledEnemy->GetController()->GetName()
				: TEXT("NULL")
			);

			// Los mandamos al pool
			PooledEnemy->SetActorHiddenInGame(true);
			PooledEnemy->SetActorEnableCollision(false);
			PooledEnemy->SetActorTickEnabled(false);

			EnemyPool.Add(PooledEnemy);
		}
	}

	// 2. Iniciamos el ciclo
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ATPEnemySpawner::TickSpawn, SpawnInterval, true);
}

void ATPEnemySpawner::TickSpawn()
{
	GetEnemyFromPool();
}

void ATPEnemySpawner::GetEnemyFromPool()
{
	for (AATPCharacterBase* Enemy : EnemyPool)
	{
		// Buscamos uno que esté "muerto" o desactivado
		if (Enemy && Enemy->IsHidden())
		{
			FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->GetComponentLocation(), SpawnArea->GetScaledBoxExtent());
			SpawnLocation.Z += 50.f; // Evitamos que spawnee enterrado

			// 1. Lo despertamos físicamente
			Enemy->SetActorLocation(SpawnLocation);
			Enemy->SetActorHiddenInGame(false);
			Enemy->SetActorEnableCollision(true);
			Enemy->SetActorTickEnabled(true);


			UE_LOG(
				LogTemp,
				Warning,
				TEXT("Enemy despertado. Controller = %s"),
				Enemy->GetController()
				? *Enemy->GetController()->GetName()
				: TEXT("NULL")
			);

          
			// 2. Reset de variables lógicas
			Enemy->health = Enemy->maxHealth;
			Enemy->isAlive = true;
			Enemy->OnRespawned();



			// 3. REINICIO DE NAVEGACIÓN (Clave para el NavMesh)
			AAIController* AIC = Cast<AAIController>(Enemy->GetController());
			if (AIC)
			{
				// Detenemos cualquier orden anterior que tuviera el "fantasma" del enemigo
				AIC->StopMovement();
              
				// Opcional: Si usas Behavior Trees, puedes reiniciarlo aquí
				// AIC->GetBrainComponent()->RestartLogic();
			}

			UE_LOG(LogTemp, Warning, TEXT("Pool: Enemigo despertado y NavMesh listo!"));
			return;
		}
	}
	UE_LOG(LogTemp, Error, TEXT("Pool: ¡No hay enemigos disponibles en la piscina!"));
}

