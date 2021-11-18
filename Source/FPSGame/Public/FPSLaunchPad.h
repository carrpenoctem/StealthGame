// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:
	
	/* probably not gonna need
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	*/

	// launch pad scene root
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneComp;

	// launch pad static mesh
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* ArrowDecal;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float Power = 1000;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	/* probably not gonna need
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	*/

};
