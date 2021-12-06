// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGuardController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FPSAIGuard.h"

AFPSGuardController::AFPSGuardController()
{

}

void AFPSGuardController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);

	// Not sure what is the use of BTComp, since BT alone does the job 
	//BehaviorTreeComponent->StartTree(*BehaviorTree);
}

// Doesn't seem useful at this point
void AFPSGuardController::OnPossess(APawn* MyPawn)
{
	Super::OnPossess(MyPawn);
}

UBlackboardComponent* AFPSGuardController::Get_Blackboard() const
{
	return Blackboard;
}

