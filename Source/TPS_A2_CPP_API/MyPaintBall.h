// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPaintBall.generated.h"

class USphereComponent;                                         //la
class UProjectileMovementComponent; //la

UCLASS(config = Game)                    //la
class TPS_A2_CPP_API_API AMyPaintBall : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)//la
	USphereComponent* CollisionComp;//la

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true")) //la
		UProjectileMovementComponent* ProjectileMovement;  //la
	
public:	
	// Sets default values for this actor's properties
	AMyPaintBall();

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit); //la

	
	USphereComponent* GetCollisionComp() const { return CollisionComp; }	
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }//
};
