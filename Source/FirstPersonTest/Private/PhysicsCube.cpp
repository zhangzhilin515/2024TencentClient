// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsCube.h"

#include "FirstPersonTest/FirstPersonTestGameMode.h"
#include "FirstPersonTest/FirstPersonTestProjectile.h"


APhysicsCube::APhysicsCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void APhysicsCube::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh = FindComponentByClass<UStaticMeshComponent>();
	if (StaticMesh != nullptr)
	{
		RootComponent = StaticMesh;

		StaticMesh->OnComponentHit.AddDynamic(this, &APhysicsCube::OnHit);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StaticMesh1 not found! Make sure it's properly set up in the Blueprint."));
	}
	HitCount = 0;
}

// Called every frame
void APhysicsCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APhysicsCube::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AFirstPersonTestProjectile* Projectile = Cast<AFirstPersonTestProjectile>(OtherActor);
	if (Projectile)
	{
		HitCount++;
		if (HitCount == 1)
		{
			FVector Scale(MultipleScale, MultipleScale, MultipleScale);
			StaticMesh->SetWorldScale3D(Scale);
		}
		else if (HitCount == 2)
		{
			if (IsImportant)
			{
				ScoreValue *= 2.0f;
			}
			AFirstPersonTestGameMode* GameMode = Cast<AFirstPersonTestGameMode>(GetWorld()->GetAuthGameMode());
			if (GameMode)
			{
				APawn* InstigatorPawn = Projectile->GetInstigator();
				if (InstigatorPawn)
				{
					APlayerController* PlayerController = Cast<APlayerController>(InstigatorPawn->GetController());
					GameMode->AddScore(PlayerController ,ScoreValue);
				}
			}
			Destroy();
		}
	}
}

