// Fill out your copyright notice in the Description page of Project Settings.

#include "MoverComponent.h"
#include "Math/Rotator.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	
	DoorTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	//Set Original Location so actor can return where it started
	OriginalLocation = GetOwner()->GetActorLocation();
	
	//Binding our float track to our UpdateTimelineComp Function's output
	UpdateFunctionFloat.BindDynamic(this, &UMoverComponent::UpdateTimelineComp);

	//If we have a float curve, bind it's graph to our update function
	if (DoorTimelineFloatCurve)
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineFloatCurve, UpdateFunctionFloat);
	}
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//When ShouldMove is true the actor will Move
	FVector TargetLocation = OriginalLocation;

	if (bShouldMove)
	{
		TargetLocation = OriginalLocation + MoveOffset;
		RotatePlatform(DeltaTime);
	}
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	float Speed = MoveOffset.Length() / MoveTime;
		
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);
}

void UMoverComponent::SetShouldMove(bool bMoveStatus)
{
	bShouldMove = bMoveStatus;
}

void UMoverComponent::OpenDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenDoor fired"));
	DoorTimelineComp->Play();
	SetIsDoorOpen(true);
}

void UMoverComponent::CloseDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("CloseDoor fired"));
	DoorTimelineComp->Reverse();
	SetIsDoorOpen(false);
}

void UMoverComponent::SetIsDoorOpen(bool bDoorStatus)
{
	bIsDoorOpen = bDoorStatus;
}

void UMoverComponent::RotatePlatform(float DeltaTime)
{
	if (RotationAmount < 1)
	{
		GetOwner()->AddActorLocalRotation(RotationAngle * DeltaTime);
		RotationAmount += DeltaTime;
	}
}

void UMoverComponent::UpdateTimelineComp(float Output)
{
	// Create and set our Door's new relative location based on the output from our Timeline Curve
	FRotator DoorNewRotation = FRotator(0.0f, Output, 0.f);
	GetOwner()->SetActorRelativeRotation(DoorNewRotation);
}

