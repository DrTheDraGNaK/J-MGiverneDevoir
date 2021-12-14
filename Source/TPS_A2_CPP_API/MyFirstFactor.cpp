// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstFactor.h"
#include "TPS_A2_CPP_APICharacter.h"


// Sets default values
AMyFirstFactor::AMyFirstFactor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
	

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));		
	RootComponent = MeshComponent;


	LetterCount = 10;

}

// Called when the game starts or when spawned
void AMyFirstFactor::BeginPlay()
{
	Super::BeginPlay();	

	MeshComponent->OnComponentHit.AddDynamic(this, &AMyFirstFactor::OnHit);

}

// Called every frame
void AMyFirstFactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyFirstFactor::OnHit(UPrimitiveComponent* HitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ATPS_A2_CPP_APICharacter* Character = Cast<ATPS_A2_CPP_APICharacter>(otherActor);
	if (Character == nullptr)
		return;

	Character->LaunchCharacter(FVector(0, 0, 2000), false, true);
	GLog->Log("OnHit");
}

void AMyFirstFactor::PrintLetterCount() 
{
	GLog->Log("LetterCount =  " + FString::FromInt(LetterCount));
}

