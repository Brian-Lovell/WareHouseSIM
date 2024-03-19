// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaActorComponent.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UStaminaActorComponent::UStaminaActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	CurrentStamina = MaxStamina;
}


// Called when the game starts
void UStaminaActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UStaminaActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetHasStamina(CheckHasStamina());
	UE_LOG(LogTemp, Warning, TEXT("Current Stamina: %f") ,CurrentStamina);
	UE_LOG(LogTemp, Warning, TEXT("Has Stamina: %s") , bHasStamina ? TEXT("true") : TEXT("fasle"));


}

void UStaminaActorComponent::ConsumeStamina()
{
	CurrentStamina = CurrentStamina - BurnRate;
}




void UStaminaActorComponent::Sprinting()
{
	if (CurrentStamina >= 0.f)
	{
		GetOwner()->GetWorldTimerManager().SetTimer(RateTimer, this, &UStaminaActorComponent::ConsumeStamina, RateDelay, true, -1);
		// CurrentStamina = CurrentStamina - BurnRate;
	}
	UE_LOG(LogTemp, Warning, TEXT("Sprinting! Current Stamina: %f "), CurrentStamina);
}

float UStaminaActorComponent::GetCurrentStamina()
{
	return CurrentStamina / MaxStamina;
}

void UStaminaActorComponent::SetHasStamina(bool bNewHasStamina)
{
	UE_LOG(LogTemp, Warning, TEXT("Set Has Stamina fired"));
	bHasStamina = bNewHasStamina;
}

bool UStaminaActorComponent::CheckHasStamina()
{
	UE_LOG(LogTemp, Warning, TEXT("Check Has Stamina fired"));
	if (CurrentStamina >= 0.f)
	{
		return true;
	}
	return false;
}

