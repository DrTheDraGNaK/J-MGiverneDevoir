// Fill out your copyright notice in the Description page of Project Settings.


#include "MyObjectPickUp.h"

// Sets default values
AMyObjectPickUp::AMyObjectPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyObjectPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyObjectPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

