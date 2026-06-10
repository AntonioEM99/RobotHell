#pragma once

#include "CoreMinimal.h"
#include "Character/ATPCharacterBase.h" // Heredamos de la nueva base
#include "TPShooterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class ATPShooterCharacter : public AATPCharacterBase
{
    GENERATED_BODY()

    /** Componentes exclusivos del jugador (La cámara) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;
    
protected:
    /** Actions de Enhanced Input (Solo para el jugador) */
    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* MouseLookAction;

    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* ShootAction;

public:
    ATPShooterCharacter(); 

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;

    /** Handlers de Input */
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);

public:
    /** Funciones de control de interfaz/movimiento */
    UFUNCTION(BlueprintCallable, Category="Input")
    virtual void DoMove(float Right, float Forward);

    UFUNCTION(BlueprintCallable, Category="Input")
    virtual void DoLook(float Yaw, float Pitch);

    UFUNCTION(BlueprintCallable, Category="Input")
    virtual void DoJumpStart();

    UFUNCTION(BlueprintCallable, Category="Input")
    virtual void DoJumpEnd();

    /** Lógica exclusiva de fin de juego y UI */
    float gameOverDelay = 3.0f;
    void RestartGameLevel();
    void UpdateHUD();


public:
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};