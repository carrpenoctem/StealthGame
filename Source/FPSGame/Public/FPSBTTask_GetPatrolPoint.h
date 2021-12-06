// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "FPSBTTask_GetPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API UFPSBTTask_GetPatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:

	// Constructor
	UFPSBTTask_GetPatrolPoint();

	// ExecuteTask override
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory);

	// Outpost bb key name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search")
	FName OutpostName = TEXT("Outpost");


};
