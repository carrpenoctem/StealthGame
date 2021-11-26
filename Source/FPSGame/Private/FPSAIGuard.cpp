// Fill out your copyright notice in the Description page of Project Settings.

#include "Perception/PawnSensingComponent.h"
#include "FPSAIGuard.h"
#include "FPSGameMode.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initializing sensing component
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	// Binding senses response
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

	InitialRotation = GetActorRotation();
	
}

// Called when pawn is seen
void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if(SeenPawn==nullptr)
	{
		return;
	}

	AFPSGameMode* MyGameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (MyGameMode)
	{
		MyGameMode->CompleteMission(SeenPawn, false);
	}

	DrawDebugLine(GetWorld(), GetActorLocation(), SeenPawn->GetActorLocation(), FColor::Red, false, 2, NULL, 5);
}

// Called when noise is heard
void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugLine(GetWorld(), GetActorLocation(), Location, FColor::Green, false, 2, NULL, 5);

	// Using this instead FindLookAtRotation to avoid adding libraries
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0;
	NewLookAt.Roll = 0;
	
	SetActorRotation(NewLookAt);

	// Return to initial rotation after a while
	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f);
}

// Reset Rotation
void AFPSAIGuard::ResetOrientation()
{
	SetActorRotation(InitialRotation);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


