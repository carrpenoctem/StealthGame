// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;
//class UBehaviorTree;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Declaring sensing component
	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* PawnSensingComp;

	// On sight event delegate
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	// On heard event
	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	// So the guard can return after being distracted
	FRotator InitialRotation;

	// Resetting rotation
	UFUNCTION()
	void ResetOrientation();

	// Reset rotation timer handle
	FTimerHandle TimerHandle_ResetOrientation;

	// Guard state
	EAIState GuardState;

	// State change events
	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnGuardStateChanged(EAIState NewState);

	/*
	* Moved to AI controller
	*	// Behavior tree setup
	*	UPROPERTY(EditAnywhere, Category = "AI")
	*	UBehaviorTree* BehaviorTree;
	* 
	*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// For exposing outposts array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TArray<AActor*> Outposts;

};
