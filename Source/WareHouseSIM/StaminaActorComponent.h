// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WAREHOUSESIM_API UStaminaActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStaminaActorComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(EditAnywhere, Category="Stamina")
	float CurrentStamina;
	
	UPROPERTY(EditAnywhere, Category="Stamina")
	float RechargeRate = 1.f;
	
	UPROPERTY(EditAnywhere, Category="Stamina")
	float BurnRate = 1.f;
};
