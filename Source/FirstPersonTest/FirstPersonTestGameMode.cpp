// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstPersonTestGameMode.h"
#include "FirstPersonTestCharacter.h"
#include "PhysicsCube.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "BaseGizmos/GizmoElementArrow.h"

AFirstPersonTestGameMode::AFirstPersonTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	TotalScore = 0;
	ConstructorHelpers::FClassFinder<APhysicsCube> TargetClass(TEXT("/Game/FirstPerson/Blueprints/BP_Cube"));
	if (TargetClass.Succeeded())
	{
		SpawnClass = TargetClass.Class;
		UE_LOG(LogTemp, Display, TEXT("Find Class Success"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Find Class Fail"));
	}
}

void AFirstPersonTestGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&AFirstPersonTestGameMode::EndGame,
		GameDuration,
		false
		);

	for (int32 i = 0; i < CubeNum; i++)
	{
		double RandomX = FMath::RandRange(250.0f, 2500.0f);
		double RandomY = FMath::RandRange(300.0f, 3500.0f);
		double RandomZ = 49.0f;
		FVector RandomLocation(RandomX, RandomY, RandomZ);
		FTransform Transform(RandomLocation);
		APhysicsCube* PhysicsCube = GetWorld()->SpawnActor<APhysicsCube>(SpawnClass, Transform);
		if (FMath::RandBool())
		{
			PhysicsCube->IsImportant = true;
		}
	}
}

void AFirstPersonTestGameMode::AddScore(APlayerController* Player, int32 Score)
{
	PlayerScores.FindOrAdd(Player) += Score;
	TotalScore += Score;
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			5.0f,
			FColor::Blue,
			FString::Printf(TEXT("Player %s Get Score : %d"), *Player->GetName(), Score)
			);
	}
}

void AFirstPersonTestGameMode::EndGame()
{
	for (const auto& PlayerScore : PlayerScores)
	{
		UE_LOG(LogTemp, Display, TEXT("Player %s: Score %i"), *PlayerScore.Key->GetName(),PlayerScore.Value);
	}
	UE_LOG(LogTemp, Display, TEXT("Total score: %i"), TotalScore);
}