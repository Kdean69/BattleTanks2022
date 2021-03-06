// Copyright © 2022 Kdean Games. All Rights Reserved.

#pragma once

#include "BaseTank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "BattleTanksAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ABattleTanksAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ABaseTank* GetControlledTank() const;

	ABaseTank* GetPlayerTank() const;

};
