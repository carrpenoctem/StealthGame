// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSGuardController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;
class UBehaviorTree;

UCLASS()
class FPSGAME_API AFPSGuardController : public AAIController
{
	GENERATED_BODY()
	
public:

	// Initializer
	AFPSGuardController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// on possess override
	virtual void OnPossess(APawn* MyPawn) override;

	// BB component (has to be by Getter or else it shows Shadowing error)
	UBlackboardComponent* Get_Blackboard() const;

public:

	// BT component
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	// Actual BT
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTree;

private:

	// BB component for the getter
	UBlackboardComponent* Blackboard;

};
