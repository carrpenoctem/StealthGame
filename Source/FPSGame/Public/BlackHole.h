// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHole();

protected:

	// Basic mesh component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	// Inner sphere collision
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* BlackHoleSphereComp;

	// Outer sphere collision
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* OuterSphereComp;

	// Collected cubes array
	UPROPERTY(VisibleAnywhere, Category = "Gameplay")
	TArray<AActor*> Cubes;

	// Sucking strength
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float strength = 1;
	
	// For invoking destruction of sucked actors
	UFUNCTION()
	void OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// For collected cubes
	UFUNCTION()
	void DisableGravity();

	// Continous suck in tick
	UFUNCTION()
	void SuckCubes();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
