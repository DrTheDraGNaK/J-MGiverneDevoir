// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPickUp.h"

// Sets default values
AMyPickUp::AMyPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	active = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;

}

// Called when the game starts or when spawned
void AMyPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMyPickUp::Interacted() 
{
	active = false;
	SetActorHiddenInGame(true);
}

bool AMyPickUp::GetActive()
{
	return active;
}


