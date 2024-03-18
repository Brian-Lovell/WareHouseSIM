// Fill out your copyright notice in the Description page of Project Settings.


#include "HingedDoorActor.h"

// Sets default values
AHingedDoorActor::AHingedDoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	SetRootComponent(DefaultSceneRoot);
	
	// DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorComponent = CreateDefaultSubobject<UHingedDoorSceneComponent>(TEXT("Hinged Door Scene Component"));

	Door->SetupAttachment(RootComponent);
	// Door->AttachToComponent(DoorFrame, FAttachmentTransformRules::KeepRelativeTransform);
	DoorComponent->AttachToComponent(Door, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AHingedDoorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHingedDoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

