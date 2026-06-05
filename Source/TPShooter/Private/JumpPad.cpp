#include "JumpPad.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

AJumpPad::AJumpPad()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	PadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PadMesh"));
	PadMesh->SetupAttachment(SceneRoot);

	LaunchTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchTrigger"));
	LaunchTrigger->SetupAttachment(SceneRoot);
	LaunchTrigger->SetBoxExtent(FVector(100.0f, 100.0f, 45.0f));
	LaunchTrigger->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));

	LaunchTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LaunchTrigger->SetCollisionObjectType(ECC_WorldDynamic);
	LaunchTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	LaunchTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	LaunchTrigger->SetGenerateOverlapEvents(true);
}

void AJumpPad::BeginPlay()
{
	Super::BeginPlay();

	if (LaunchTrigger)
	{
		LaunchTrigger->OnComponentBeginOverlap.AddDynamic(this, &AJumpPad::OnLaunchTriggerBeginOverlap);
	}
}

void AJumpPad::OnLaunchTriggerBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (!Character)
	{
		return;
	}

	if (bOnlyPlayer && !Character->IsPlayerControlled())
	{
		return;
	}

	const float CurrentTime = GetWorld()->GetTimeSeconds();

	if (CurrentTime - LastLaunchTime < Cooldown)
	{
		return;
	}

	LastLaunchTime = CurrentTime;

	const FVector LaunchDirection =
		(GetActorUpVector() * UpForce) +
		(GetActorForwardVector() * ForwardForce);

	Character->LaunchCharacter(LaunchDirection, false, true);
}