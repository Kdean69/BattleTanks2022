// Copyright © 2022 Kdean Games. All Rights Reserved.

#include "../BattleTanks.h"
#include "BattleTanksPlayerController.h"
#include "BaseTank.h"

void ABattleTanksPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("BattleTanksPlayerController not posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BattleTanksPlayerController posessing: %s"),
			*ControlledTank->GetName());
	}

}

void ABattleTanksPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Aim towards crosshair
	AimTowardsCrosshair();
}

ABaseTank* ABattleTanksPlayerController::GetControlledTank() const
{
	return Cast<ABaseTank>(GetPawn());
}

void ABattleTanksPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out param
	
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}

}

bool ABattleTanksPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(
		ViewportSizeX * CrosshairXLocation, 
		ViewportSizeY * CrosshairYLocation);

	FVector LookDirection;
	// "De-project" screen position of the crosshair to a world lirection
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along look direction, see what we hit (up to MAX range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return true;
}

bool ABattleTanksPlayerController::GetLookDirection(
	FVector2D ScreenLocation,
	FVector& LookDirection) const
{
	FVector CameraWorldLocation; // TODO: to be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
}

bool ABattleTanksPlayerController::GetLookVectorHitLocation(
	FVector LookDirection, 
	FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Linetrace didn't succeed

}
