// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbingTriggerComponent.h"

// Sets default values for this component's properties
UClimbingTriggerComponent::UClimbingTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UClimbingTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Actor = GetClimber();

	if (Actor != nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("%s "), *Actor->GetName())
	}
}

void UClimbingTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Display, TEXT("Climbing Trigger Component hit Begin Play"));
}

AActor* UClimbingTriggerComponent::GetClimber() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		return Actor;
	}

	
	return nullptr;
}
