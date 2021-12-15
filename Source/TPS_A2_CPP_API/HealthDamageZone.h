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
		class ATPS_A2_CPP_APICharacter* Character;

	UPROPERTY(EditAnywhere)
		bool isDamage;

	UPROPERTY(EditAnywhere)
		bool isLava;

	UPROPERTY()
		FTimerHandle Handle;


	UPROPERTY()
		int LevelOfDamage;





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		float time;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnActorBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnActorEndOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex);

};
