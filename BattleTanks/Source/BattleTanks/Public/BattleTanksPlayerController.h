// Copyright © 2022 Kdean Games. All Rights Reserved.

#pragma once

#include "BaseTank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleTanksPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ABattleTanksPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ABaseTank* GetControlledTank() const;

	// Start tank move barrel to aim point
	void AimTowardsCrosshair();

	// Return OUT Param, true if hits landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.05f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;
};
