// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbableActor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NetworkGuy.h"
#include "Components/BoxComponent.h"

// Sets default values
AClimbableActor::AClimbableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ClimbingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Climbing Mesh"));
	RootComponent = ClimbingMesh;
	
	ClimbingTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Climbing Trigger Box"));
	ClimbingTriggerBox->SetupAttachment(ClimbingMesh);

	ClimbingTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AClimbableActor::OnOverlapBegin);
	ClimbingTriggerBox->OnComponentEndOverlap.AddDynamic(this, &AClimbableActor::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AClimbableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClimbableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClimbableActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ANetworkGuy* PlayerCharacter = Cast<ANetworkGuy>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->StartClimbing();
	}
}

void AClimbableActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ANetworkGuy* PlayerCharacter = Cast<ANetworkGuy>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->StopClimbing();
	}
}


