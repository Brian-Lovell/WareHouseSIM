// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
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
	
	// Swinging Doors
	void OpenDoor();
	void CloseDoor();
	void SetIsDoorOpen(bool bDoorStatus);

	// Variable for Door Curve Asset
	UPROPERTY(EditAnywhere, Category="Door")
	UCurveFloat* DoorTimelineFloatCurve;

	UPROPERTY(EditAnywhere, Category="Door")
	bool bIsDoorOpen = false;

	// Set if actor should move
	void SetShouldMove(bool bMoveStatus);
	
	UPROPERTY(EditAnywhere, Category="Movement")
	bool bShouldMove = false;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//TimelineComponent to animate Door meshes
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DoorTimelineComp;
	
private:
	UPROPERTY(EditAnywhere, Category="Movement")
	FVector MoveOffset;

	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveTime = 4;

	UPROPERTY(EditAnywhere, Category="Rotation")
	FRotator RotationAngle;
	
	float RotationAmount = 0;

	void RotatePlatform(float DeltaTime);

	FVector OriginalLocation;
	
	//Float Track Signature to handle our update track event
	FOnTimelineFloat UpdateFunctionFloat;

	//Function which updates our Door's relative location with the timeline graph
	UFUNCTION()
	void UpdateTimelineComp(float Output);
	
};
