#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Gun.h" // Necesitamos conocer la clase del arma
#include "ATPCharacterBase.generated.h"

UCLASS(Abstract) // Abstract porque no queremos spawnear una "base" solita
class TPSHOOTER_API AATPCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AATPCharacterBase();

protected:
	virtual void BeginPlay() override;

	// Lógica de daño compartida
	UFUNCTION()
	void OnDamageTaken(AActor* damagedActor, float Damage, const class UDamageType* DamageType, class AController* instigatedBy, AActor* DamageCauser);

public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Shoot();

	UFUNCTION()
	virtual void HealingPlayer(float medkit);

	// Variables de combate (Protected para que los hijos las vean)
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<AGun> gunClass;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	AGun* currentGun;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float maxHealth = 100.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	float health;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	bool isAlive = true;


};