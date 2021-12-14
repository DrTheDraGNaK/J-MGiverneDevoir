// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthDamageZone.h"
#include "Components/BoxComponent.h"

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
	/*CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AHealthDamageZone::OnOverlapBegin);
	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &AHealthDamageZone::OnOverlapEnd);*/
}

// Called every frame
void AHealthDamageZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void AHealthDamageZone::OnOverlapBegin() 
//{
//
//}

