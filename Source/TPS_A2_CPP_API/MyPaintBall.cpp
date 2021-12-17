// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPaintBall.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"

// Sets default values

AMyPaintBall::AMyPaintBall()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AMyPaintBall::OnHit);




	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	RootComponent = CollisionComp;


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = 6.0f;
}

void AMyPaintBall::BeginPlay()
{
	Super::BeginPlay();
	//CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyPaintBall::OnBeginOverlap);
}


void AMyPaintBall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		FRotator rotation = GetActorRotation() + FRotator(-90, 0, 0);

		ADecalActor* decal = GetWorld()->SpawnActor<ADecalActor>(GetActorLocation(), rotation);
		decal->SetDecalMaterial(M_Splatters);
		decal->GetDecal()->DecalSize = FVector(100, 100, 100);
		decal->GetDecal()->SetFadeOut(1, 3, true);


		Destroy();
	}
}


//void AMyPaintBall::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	FRotator rotation = GetActorRotation() + FRotator(-90, 0, 0);
//
//	ADecalActor* decal = GetWorld()->SpawnActor<ADecalActor>(GetActorLocation(), rotation);
//	decal->SetDecalMaterial(M_Splatters);
//	decal->GetDecal()->DecalSize = FVector(100, 100, 100);
//	decal->GetDecal()->SetFadeOut(1, 3, true);
//
//	Destroy();
//}