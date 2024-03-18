// Fill out your copyright notice in the Description page of Project Settings.


#include "HingedDoorSceneComponent.h"

// Sets default values for this component's properties
UHingedDoorSceneComponent::UHingedDoorSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));
}


// Called when the game starts
void UHingedDoorSceneComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//Binding our float track to our UpdateTimelineComp Function's output
	UpdateFunctionFloat.BindDynamic(this, &UHingedDoorSceneComponent::UpdateTimelineComp);

	//If we have a float curve, bind it's graph to our update function
	if (DoorTimelineFloatCurve)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineFloatCurve, UpdateFunctionFloat);
	}
	
}

void UHingedDoorSceneComponent::UpdateTimelineComp(float Output)
{
	UStaticMeshComponent* DoorMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	// Create and set our Door's new relative location based on the output from our Timeline Curve
	FRotator DoorNewRotation = FRotator(0.0f, Output, 0.f);
	DoorMesh->SetRelativeRotation(DoorNewRotation);
}


// Called every frame
void UHingedDoorSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHingedDoorSceneComponent::OpenDoor()
{
	DoorTimelineComp->Play();
	SetIsDoorOpen(true);
}

void UHingedDoorSceneComponent::CloseDoor()
{
	DoorTimelineComp->Reverse();
	SetIsDoorOpen(false);
}

void UHingedDoorSceneComponent::SetIsDoorOpen(bool bDoorStatus)
{
	bIsDoorOpen = bDoorStatus;
}