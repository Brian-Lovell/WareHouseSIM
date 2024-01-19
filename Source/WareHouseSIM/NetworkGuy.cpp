// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGuy.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"


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
	UE_LOG(LogTemp, Display, TEXT("I'm sprinting!"));
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
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ANetworkGuy::Jump);
			EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ANetworkGuy::CrouchDown);
			EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ANetworkGuy::StandUp);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ANetworkGuy::Sprint);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ANetworkGuy::Sprint);
	}
}
