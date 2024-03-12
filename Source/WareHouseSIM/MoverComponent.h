// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WAREHOUSESIM_API UMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoverComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Set if actor should move
	void SetShouldMove(bool bMoveStatus);
	
	// Swinging Doors
	void OpenDoor();
	void CloseDoor();

	void SetIsDoorOpen(bool bDoorStatus);
	
	UPROPERTY(EditAnywhere, Category="Movement")
	bool bShouldMove = false;

	UPROPERTY(EditAnywhere, Category="Door")
	bool bIsDoorOpen = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category="Movement")
	FVector MoveOffset;

	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveTime = 4;

	UPROPERTY(EditAnywhere, Category="Rotation")
	FRotator RotationAngle;

	UPROPERTY(EditAnywhere, Category="Rotation")
	float RotationAmount = 0;

	void RotatePlatform(float DeltaTime);

	FVector OriginalLocation;
	FRotator OriginalRotation;
	
		
};
