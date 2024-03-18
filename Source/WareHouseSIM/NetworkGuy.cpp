// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGuy.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "StaminaActorComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"


// Sets default values
ANetworkGuy::ANetworkGuy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ANetworkGuy::StartClimbing()
{
	SetIsClimbing(true);
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->SetMovementMode(MOVE_Flying);
}

void ANetworkGuy::StopClimbing()
{
	SetIsClimbing(false);
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->SetMovementMode(MOVE_Walking);
}

void ANetworkGuy::SetIsClimbing(bool NewIsClimbing)
{
	bIsClimbing = NewIsClimbing;
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
	const FVector Right = GetActorRightVector();
	const FVector UP = GetActorUpVector();
	
	if(bIsClimbing)
	{
		AddMovementInput(UP,MoveVector.Y);
	}
	else
	{
	AddMovementInput(Forward, MoveVector.Y);
	AddMovementInput(Right, MoveVector.X);	
	}
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

void ANetworkGuy::CrouchDown()
{
	Crouch();
}

void ANetworkGuy::StandUp()
{
	UnCrouch();
}

void ANetworkGuy::Sprint(const FInputActionInstance& Instance)
{
	UStaminaActorComponent* StaminaComponent = GetOwner()->FindComponentByClass<UStaminaActorComponent>();
	bool bSprinting = Instance.GetValue().Get<bool>();
	if (bSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed * SprintModifier;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
	}
}

void ANetworkGuy::CustomJump()
{
	SetIsClimbing(false);
	Jump();
}

void ANetworkGuy::Interact()
{
	UE_LOG(LogTemp, Display, TEXT("Interact Pushed!"))
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ANetworkGuy::CustomJump);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ANetworkGuy::CrouchDown);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ANetworkGuy::StandUp);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ANetworkGuy::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ANetworkGuy::Sprint);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ANetworkGuy::Interact);
	}
}
