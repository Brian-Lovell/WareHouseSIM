// Fill out your copyright notice in the Description page of Project Settings.


#include "HingedDoorComponent.h"

// Sets default values for this component's properties
UHingedDoorComponent::UHingedDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));
}


// Called when the game starts
void UHingedDoorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//Binding our float track to our UpdateTimelineComp Function's output
	UpdateFunctionFloat.BindDynamic(this, &UHingedDoorComponent::UpdateTimelineComp);

	//If we have a float curve, bind it's graph to our update function
	if (DoorTimelineFloatCurve)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineFloatCurve, UpdateFunctionFloat);
	}
	
}

void UHingedDoorComponent::UpdateTimelineComp(float Output)
{
	// Create and set our Door's new relative location based on the output from our Timeline Curve
	FRotator DoorNewRotation = FRotator(0.0f, Output, 0.f);
	GetOwner()->SetActorRelativeRotation(DoorNewRotation);
}


// Called every frame
void UHingedDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHingedDoorComponent::OpenDoor()
{
	DoorTimelineComp->Play();
	SetIsDoorOpen(true);
}

void UHingedDoorComponent::CloseDoor()
{
	DoorTimelineComp->Reverse();
	SetIsDoorOpen(false);
}

void UHingedDoorComponent::SetIsDoorOpen(bool bDoorStatus)
{
	bIsDoorOpen = bDoorStatus;
}

