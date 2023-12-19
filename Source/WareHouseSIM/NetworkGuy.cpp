// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGuy.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

// Sets default values
ANetworkGuy::ANetworkGuy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANetworkGuy::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
			UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(NetworkGuyMappingContext, 0);
		}
	}
	
}

void ANetworkGuy::Move(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2d>();
	
	const FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward, MoveVector.Y);
	const FVector Right = GetActorRightVector();
	AddMovementInput(Right, MoveVector.X);
}

void ANetworkGuy::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2d>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

// Called every frame
void ANetworkGuy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANetworkGuy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANetworkGuy::Move);
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANetworkGuy::Look);
	}
}
