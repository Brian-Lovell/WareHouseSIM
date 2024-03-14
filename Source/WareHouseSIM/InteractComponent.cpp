// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"

#include "HingedDoorComponent.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * InteractHoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}

}

void UInteractComponent::Interact()
{
	// UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	FHitResult HitResult;
	bool HasHit = GetInteractionInReach(HitResult);
	if (HasHit)
	{
		// DrawDebugSphere(GetWorld(), HitResult.Location, 10, 100, FColor::Green, false, 5);
		// DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 100, FColor::Green, false, 5);
		// UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		AActor* HitActor = HitResult.GetActor();
		FName LiftTag = "LiftObject";
		FName DoorTag = "DoorObject";
		
		if (HitActor->ActorHasTag(LiftTag) == true)
		{
			// HitComponent->SetSimulatePhysics(true);
			// HitComponent->WakeAllRigidBodies();
			//
			// HitActor->Tags.Add("Grabbed");
			// HitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			// PhysicsHandle->GrabComponentAtLocationWithRotation(
			// 	HitResult.GetComponent(),
			// 	NAME_None,
			// 	HitResult.ImpactPoint,
			// 	GetComponentRotation()
			// );
			// return;
			LiftObject(HitResult, HitActor);
		}

		if (HitActor->ActorHasTag(DoorTag) == true)
		{
			UHingedDoorComponent* DoorComp = HitActor->FindComponentByClass<UHingedDoorComponent>();
			bool bDoorStatus = DoorComp->bIsDoorOpen;
			if (bDoorStatus == false)
			{
				DoorComp->OpenDoor();
			}
			else
			{
				DoorComp->CloseDoor();
			}
		}
	}
}

void UInteractComponent::Release()
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
	{
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies(); 
		PhysicsHandle->ReleaseComponent();
	}
}

void UInteractComponent::LiftObject(FHitResult& InHitResult, AActor* InHitActor)
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	UPrimitiveComponent* HitComponent = InHitResult.GetComponent();
	
	HitComponent->SetSimulatePhysics(true);
	HitComponent->WakeAllRigidBodies();
		
	InHitActor->Tags.Add("Grabbed");
	InHitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	PhysicsHandle->GrabComponentAtLocationWithRotation(
		InHitResult.GetComponent(),
		NAME_None,
		InHitResult.ImpactPoint,
		GetComponentRotation()
	);
	return;
	
}


UPhysicsHandleComponent* UInteractComponent::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber requires a UPhysicsHandleComponent"));
	}

	return Result;
}

bool UInteractComponent::GetInteractionInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxInteractDistance;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	FCollisionShape Sphere = FCollisionShape::MakeSphere(InteractRadius);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere,
		Params
	);
}

