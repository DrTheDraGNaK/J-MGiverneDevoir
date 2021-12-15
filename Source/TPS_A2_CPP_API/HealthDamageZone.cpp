// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthDamageZone.h"
#include "Components/BoxComponent.h"
#include "TPS_A2_CPP_APICharacter.h"

// Sets default values
AHealthDamageZone::AHealthDamageZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("CollisionMesh"));
	SetRootComponent(CollisionMesh);

	

}

// Called when the game starts or when spawned
void AHealthDamageZone::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AHealthDamageZone::OnActorBeginOverlap);
	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &AHealthDamageZone::OnActorEndOverlap);

	if (isDamage)
		LevelOfDamage = -5;
	else
		LevelOfDamage = 5;

	
}

// Called every frame
void AHealthDamageZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthDamageZone::OnActorBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Character = Cast<ATPS_A2_CPP_APICharacter>(OtherActor);

	FTimerDelegate timerDelegate;
	timerDelegate.BindUFunction(Character, FName("life"), LevelOfDamage);
	GetWorldTimerManager().SetTimer(Handle, timerDelegate, 1, true);
}

void AHealthDamageZone::OnActorEndOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex)
{
	GetWorldTimerManager().ClearTimer(Handle);
}


