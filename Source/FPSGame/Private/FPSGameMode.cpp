// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

// Input disable and camera effect on succeed
void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn) 
	{
		InstigatorPawn->DisableInput(nullptr);
		OnMissionCompleted(InstigatorPawn);

		APlayerController* playerController = Cast<APlayerController>(InstigatorPawn->GetController());
		if (playerController) 
		{
			TArray<AActor*> newTargetsArray;
			UGameplayStatics::GetAllActorsWithTag(this, FName(TEXT("CameraBlendActor")), newTargetsArray);

			if(newTargetsArray.Num()>0)
			{
				playerController->SetViewTargetWithBlend(newTargetsArray[0], 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
			}
			
		}
	}
}
