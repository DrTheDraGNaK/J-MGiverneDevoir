// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "TPS_A2_CPP_APICharacter.h"


// Sets default values
AObstacle::AObstacle()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneComponent);

	StaticMesh->OnComponentHit.AddDynamic(this, &AObstacle::OnObstacleHit);


}

void AObstacle::OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ATPS_A2_CPP_APICharacter* TPS_A2_CPP_APICharacter = Cast<ATPS_A2_CPP_APICharacter>(OtherActor);

	//if (TPS_A2_CPP_APICharacter)
	//{
	//	//TPS_A2_CPP_APICharacter->Death();
	//}

}





