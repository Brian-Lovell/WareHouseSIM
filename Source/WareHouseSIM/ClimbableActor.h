// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClimbableActor.generated.h"

UCLASS()
class WAREHOUSESIM_API AClimbableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClimbableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* ClimbingTriggerBox;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ClimbingMesh;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
		);

	AActor* GetClimber() const;

};
