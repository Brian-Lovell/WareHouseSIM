// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "NetworkGuy.generated.h"

class UInputMappingContext;
class UInputAction;
struct  FInputActionValue;


UCLASS()
class WAREHOUSESIM_API ANetworkGuy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANetworkGuy();

	void StartClimbing();

	void StopClimbing();

	void SetIsClimbing(bool bIsClimbing);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* NetworkGuyMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* CrouchAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float SprintModifier = 2.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float DefaultSpeed = 600.f;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void CrouchDown();
	void StandUp();
	void Sprint(const FInputActionInstance& Instance);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	bool bIsClimbing = false;
	

};
