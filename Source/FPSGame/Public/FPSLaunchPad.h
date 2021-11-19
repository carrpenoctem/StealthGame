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

	// launch pad scene root
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneComp;

	// launch pad static mesh
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	// Additional decal
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* ArrowDecal;

	// Base launch power
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float Power = 1000;

	// Base launch angle
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float Angle = 45;

	// Particle to trigger on launch
	UPROPERTY(EditDefaultsOnly, Category = "FX");
	UParticleSystem* LaunchFX;

	// Overlap check
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
