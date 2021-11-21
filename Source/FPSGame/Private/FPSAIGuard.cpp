// Fill out your copyright notice in the Description page of Project Settings.

#include "Perception/PawnSensingComponent.h"
#include "FPSAIGuard.h"
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
	
}

// Called when pawn is seen
void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if(SeenPawn==nullptr)
	{
		return;
	}
	DrawDebugLine(GetWorld(), GetActorLocation(), SeenPawn->GetActorLocation(), FColor::Red, false, 2, NULL, 5);
}

// Called when noise is heard
void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugLine(GetWorld(), GetActorLocation(), Location, FColor::Green, false, 2, NULL, 5);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


