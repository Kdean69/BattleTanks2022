// Copyright © 2022 Kdean Games. All Rights Reserved.

#include "BattleTanksAIController.h"
#include "../BattleTanks.h"

void ABattleTanksAIController::BeginPlay()
{
	Super::BeginPlay();

	auto AIControlledTank = GetPlayerTank();
	if (!AIControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Battle Tanks AIController not posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found player: %s"), *AIControlledTank->GetName());
	}
}

void ABattleTanksAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		// TODO Move towards player

		// Aim towards player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// TODO Fire if ready
	}
}

ABaseTank* ABattleTanksAIController::GetControlledTank() const
{
	return Cast<ABaseTank>(GetPawn());
}

ABaseTank* ABattleTanksAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank) { return nullptr; }
	return Cast<ABaseTank>(PlayerTank);
}
