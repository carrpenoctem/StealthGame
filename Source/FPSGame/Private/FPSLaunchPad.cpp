// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/DecalComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "FPSLaunchPad.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	// Creating scene comp as a default root
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = SceneComp;

	// Adding mesh comp and setting up collisions
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MeshComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	MeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	MeshComp->SetupAttachment(RootComponent);

	// Overlap event binding
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::HandleOverlap);

	// Adding a decal
	ArrowDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	ArrowDecal->SetupAttachment(RootComponent);
}

// Launch character or actor on overlap + particle effect
void AFPSLaunchPad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Try to launch character if cast succeeds
	ACharacter* MyPawn = Cast<ACharacter>(OtherActor);
	if (MyPawn)
	{
		MyPawn->LaunchCharacter((GetActorForwardVector()+GetActorUpVector()) * Power,true,true);
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
	}
	else 
	{
		// Try to launch actor
		UStaticMeshComponent* CubeComp = Cast<UStaticMeshComponent>(OtherComp);
		if (CubeComp)
		{
			float CubeMass = CubeComp->GetMass();
			CubeComp->AddImpulse((GetActorForwardVector() + GetActorUpVector()) * Power*CubeMass);
			UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
		}
	}

}

