#include "TPShooterCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TPShooterPlayerController.h"
#include "Kismet/GameplayStatics.h" // Importante para OpenLevel

ATPShooterCharacter::ATPShooterCharacter()
{
    // Mantenemos la configuración física básica
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
       
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

    // Movimiento del jugador
    GetCharacterMovement()->JumpZVelocity = 500.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;

    // --- CÁMARAS: Esto es lo que NO tendrá el enemigo ---
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

void ATPShooterCharacter::BeginPlay()
{
    // El Super llama a AATPCharacterBase::BeginPlay(), que spawnea el arma y setea la vida
    Super::BeginPlay();

    // Lógica visual específica del jugador
    GetMesh()->HideBoneByName("weapon_r", EPhysBodyOp::PBO_None);
    
    // Inicializamos el HUD
    UpdateHUD();
}

void ATPShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Llamamos al Super por buena práctica, aunque ACharacter::SetupPlayerInputComponent suela estar vacío
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
    {
        // Salto: Usamos tus métodos personalizados que envuelven la lógica de Jump
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATPShooterCharacter::DoJumpStart);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATPShooterCharacter::DoJumpEnd);

        // Movimiento y Cámara
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPShooterCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPShooterCharacter::Look);
        EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ATPShooterCharacter::Look);

        // Disparo: Llama a Shoot(), que ahora reside en AATPCharacterBase
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ATPShooterCharacter::Shoot);
    }
    else
    {
        // Log de error por si falla el cast (útil para debuguear)
        UE_LOG(LogTemp, Error, TEXT("Fallo al encontrar Enhanced Input Component"));
    }
}

void ATPShooterCharacter::UpdateHUD()
{
    ATPShooterPlayerController* playerController = Cast<ATPShooterPlayerController>(GetController());
    if (playerController && playerController->hudWidget)
    {
       // Usamos health y maxHealth que vienen de la clase Base
       playerController->hudWidget->SetPorcent(health / maxHealth);
       
       if (health <= 0)
       {
          FTimerHandle gameOverHandle;
          GetWorldTimerManager().SetTimer(gameOverHandle, this, &ATPShooterCharacter::RestartGameLevel, gameOverDelay, false);
       }
    }
}

// --- LOGICA DE MOVIMIENTO (Se queda aquí porque es para el Player) ---

void ATPShooterCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    DoMove(MovementVector.X, MovementVector.Y);
}

void ATPShooterCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();
    DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ATPShooterCharacter::DoMove(float Right, float Forward)
{
    if (GetController() != nullptr)
    {
       const FRotator Rotation = GetController()->GetControlRotation();
       const FRotator YawRotation(0, Rotation.Yaw, 0);
       const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
       const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

       AddMovementInput(ForwardDirection, Forward);
       AddMovementInput(RightDirection, Right);
    }
}

void ATPShooterCharacter::DoLook(float Yaw, float Pitch)
{
    AddControllerYawInput(Yaw);
    AddControllerPitchInput(Pitch);
}

void ATPShooterCharacter::DoJumpStart()
{
    // Llama a la función Jump() heredada de ACharacter
    Jump();
}

void ATPShooterCharacter::DoJumpEnd()
{
    // Llama a StopJumping() heredada de ACharacter
    StopJumping();
}

void ATPShooterCharacter::RestartGameLevel()
{
    UGameplayStatics::OpenLevel(GetWorld(), FName(*UGameplayStatics::GetCurrentLevelName(GetWorld())));
}