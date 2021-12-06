// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBTTask_GetPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "FPSGuardController.h"
#include "FPSAIGuard.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UFPSBTTask_GetPatrolPoint::UFPSBTTask_GetPatrolPoint()
{
	
}

EBTNodeResult::Type UFPSBTTask_GetPatrolPoint::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// Get AI controller and Pawn
	AFPSGuardController* MyController = Cast<AFPSGuardController>(owner_comp.GetAIOwner());
	AFPSAIGuard* MyPawn = Cast<AFPSAIGuard>(MyController->GetPawn());

	// Get outposts array
	TArray<AActor*> Outposts = MyPawn->Outposts;

	// Try to get current outpost
	AActor* CurrentOutpost = Cast<AActor>(MyController->GetBlackboardComponent()->GetValueAsObject(OutpostName));
	
	// Outpost index initialize
	int newIndex = 0;

	// If current outpost exists, pick another
	if (CurrentOutpost)
	{
		newIndex = Outposts.Find(CurrentOutpost) + 1;
		if (newIndex >= Outposts.Num())
		{
			newIndex = 0;
		}
	}

	// Set new current outpost
	CurrentOutpost = Outposts[newIndex];

	// Set value in BB
	MyController->GetBlackboardComponent()->SetValueAsObject(OutpostName, CurrentOutpost);

	return EBTNodeResult::Type();
}
