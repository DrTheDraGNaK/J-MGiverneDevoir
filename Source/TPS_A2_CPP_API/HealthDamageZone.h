// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthDamageZone.generated.h"

UCLASS()
class TPS_A2_CPP_API_API AHealthDamageZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthDamageZone();

	UPROPERTY()
	class UBoxComponent* CollisionMesh;

	UPROPERTY()
	bool IsRange;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*UFUNCTION()
	void OnActorBeginOverlap();

	UFUNCTION()
		void OnActorEndOverlap();*/

};
