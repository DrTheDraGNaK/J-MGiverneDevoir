// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHealth.h"
#include "TPS_A2_CPP_APICharacter.h"

// Sets default values
AMyHealth::AMyHealth()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;

}

// Called when the game starts or when spawned
void AMyHealth::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentHit.AddDynamic(this, &AMyHealth::OnHit);
	
}

// Called every frame
void AMyHealth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyHealth::OnHit(UPrimitiveComponent* HitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ATPS_A2_CPP_APICharacter* Character = Cast<ATPS_A2_CPP_APICharacter>(otherActor);
	if (Character == nullptr)
		return;

	/*Character->LaunchCharacter(FVector(0, 0, 2000), false, true);*/
	GLog->Log("OnHit");
}

