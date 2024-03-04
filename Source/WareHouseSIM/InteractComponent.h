// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WAREHOUSESIM_API UInteractComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BluePrintCallable)
	void Interact();
	
	UFUNCTION(BluePrintCallable)
	void Release();
	
private:
	UPROPERTY(EditAnywhere, Category = Input)
	float MaxInteractDistance = 400;

	UPROPERTY(EditAnywhere, Category = Input)
	float InteractRadius = 100;

	UPROPERTY(EditAnywhere, Category = Input)
	float InteractHoldDistance = 200;

	UPhysicsHandleComponent* GetPhysicsHandle() const;

	bool GetInteractionInReach(FHitResult& OutHitResult) const;
};
