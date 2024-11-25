// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsCube.h"
#include "GameFramework/GameModeBase.h"
#include "FirstPersonTestGameMode.generated.h"

UCLASS(minimalapi)
class AFirstPersonTestGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	FTimerHandle TimerHandle;
public:
	AFirstPersonTestGameMode();

	TSubclassOf<APhysicsCube> SpawnClass;
	
	TMap<APlayerController*, int32> PlayerScores;

	UPROPERTY(BluePrintReadWrite, VisibleAnywhere)
	int32 TotalScore = 0;

	UPROPERTY(BluePrintReadWrite, VisibleAnywhere)
	float GameDuration = 10.0f;

	UPROPERTY(BluePrintReadWrite, VisibleAnywhere)
	int32 CubeNum = 10;

	void AddScore(APlayerController* PlayerController, int32 Score);
	void EndGame();
};



