// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BlackHole.h"

// Sets default values
ABlackHole::ABlackHole()
{
	// Setting black hole mesh
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	// Setting up black hole sphere
	BlackHoleSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	BlackHoleSphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BlackHoleSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	BlackHoleSphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	BlackHoleSphereComp->SetupAttachment(MeshComp);

	// Setting up outer sphere
	OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OuterSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OuterSphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	OuterSphereComp->SetupAttachment(MeshComp);

	// Overlap for InnerSphere
	BlackHoleSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	DisableGravity();
	
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ABlackHole::SuckCubes();

}

// Destroying actors that were sucked in
void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Initial gravity disable for all overlapping cubes
void ABlackHole::DisableGravity() 
{
	OuterSphereComp->GetOverlappingActors(Cubes);

	for (int32 i = 0; i < Cubes.Num(); i++)
	{
		AActor* currentCube = Cubes[i];
		UPrimitiveComponent* comp = Cast<UPrimitiveComponent>(currentCube->GetComponentByClass(UPrimitiveComponent::StaticClass()));
		comp->SetEnableGravity(false);
	}
}

// using AddForce to suck cubes towards the center
void ABlackHole::SuckCubes()
{
	if (Cubes.Num() > 0)
	{
		for (int32 i = 0; i < Cubes.Num(); i++)
		{
			AActor* currentCube = Cubes[i];
			const float forceMultiplier = OuterSphereComp->GetScaledSphereRadius() - (GetActorLocation() - currentCube->GetActorLocation()).Size();
			UPrimitiveComponent* comp = Cast<UPrimitiveComponent>(currentCube->GetComponentByClass(UPrimitiveComponent::StaticClass()));
			comp->AddForce((GetActorLocation() - currentCube->GetActorLocation()) * strength * forceMultiplier);
		}
	}
}

