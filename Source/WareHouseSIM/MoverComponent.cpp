// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverComponent.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	//Set Original Location so actor can return where it started
	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//When ShouldMove is true the actor will Move
	FVector TargetLocation = OriginalLocation;

	if (ShouldMove)
	{
		TargetLocation = OriginalLocation + MoveOffset;
		RotatePlatform(DeltaTime);
	}
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	float Speed = MoveOffset.Length() / MoveTime;
		
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
	GetOwner()->SetActorLocation(NewLocation);
}

void UMoverComponent::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;
}

void UMoverComponent::RotatePlatform(float DeltaTime)
{
	if (RotationAmount < 1)
	{
		GetOwner()->AddActorLocalRotation(RotationAngle * DeltaTime);
		RotationAmount += DeltaTime;
	}
}
