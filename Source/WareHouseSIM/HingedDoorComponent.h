// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "HingedDoorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WAREHOUSESIM_API UHingedDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHingedDoorComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Hinged Doors
	void OpenDoor();
	void CloseDoor();
	void SetIsDoorOpen(bool bDoorStatus);
	bool bIsDoorOpen = false;

	UPROPERTY(EditAnywhere, Category="Hinged Door")
	UCurveFloat* DoorTimelineFloatCurve;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Add Timeline Component to animate door swing.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DoorTimelineComp;

private:
	//Float Track Signature to handle our update track event
	FOnTimelineFloat UpdateFunctionFloat;

	//Function which updates our Door's relative location with the timeline graph
	UFUNCTION()
	void UpdateTimelineComp(float Output);

		
};
