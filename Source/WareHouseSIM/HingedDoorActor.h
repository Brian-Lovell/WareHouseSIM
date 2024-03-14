// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HingedDoorSceneComponent.h"
#include "GameFramework/Actor.h"
#include "HingedDoorActor.generated.h"

UCLASS()
class WAREHOUSESIM_API AHingedDoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHingedDoorActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DoorFrame;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Door;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UHingedDoorSceneComponent* DoorComponent;
	

};
