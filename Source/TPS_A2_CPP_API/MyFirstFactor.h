// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFirstFactor.generated.h"

UCLASS()
class TPS_A2_CPP_API_API AMyFirstFactor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFirstFactor();

	UPROPERTY(EditAnywhere)
		int LetterCount;

	

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* MeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& Hit);

	//Creation de la fonction
	UFUNCTION(BlueprintCallable) //Permet de faire une node utilisable dans le BluePrint
	void PrintLetterCount();

};
