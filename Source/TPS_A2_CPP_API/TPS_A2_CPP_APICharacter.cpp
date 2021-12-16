// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPS_A2_CPP_APICharacter.h"




#include"MyPaintBall.h"





#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ATPS_A2_CPP_APICharacter

ATPS_A2_CPP_APICharacter::ATPS_A2_CPP_APICharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	collectionRange = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionRange"));
	collectionRange->AttachTo(RootComponent);
	collectionRange->SetSphereRadius(100.0f);

}

//void ATPS_A2_CPP_APICharacter::Death()
//{
//	if (!bIsDead) 
//	{
//		const FVector Location = GetActorLocation();
//
//		UWorld* World = GetWorld();
//		if (World)
//		{
//			bIsDead = true;
//			DisableInput(nullptr);
//
//			if (DeathParticleSystem)
//			{
//				UGameplayStatics::SpawnEmitterAtLocation(World, DeathParticleSystem, Location);
//			}
//
//			if (DeathSound)
//			{
//				UGameplayStatics::PlaySoundAtLocation(World, DeathSound, Location);
//			}
//
//			GetMesh()->SetVisibility(false);
//
//			World->GetTimerManager().SetTimer(RestartTimerHandle, this, &ATPS_A2_CPP_APICharacter::OnDeath, 1.f);
//		}
//	}
//	
//
//}


//////////////////////////////////////////////////////////////////////////
// Input

void ATPS_A2_CPP_APICharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ATPS_A2_CPP_APICharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ATPS_A2_CPP_APICharacter::OnStopRun);



	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATPS_A2_CPP_APICharacter::Fire);


	PlayerInputComponent->BindAxis("MoveForward", this, &ATPS_A2_CPP_APICharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPS_A2_CPP_APICharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATPS_A2_CPP_APICharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATPS_A2_CPP_APICharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATPS_A2_CPP_APICharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATPS_A2_CPP_APICharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATPS_A2_CPP_APICharacter::OnResetVR);


	//PickUp Object
	InputComponent->BindAction("Pickup", IE_Pressed, this, &ATPS_A2_CPP_APICharacter::Interact);
}

void ATPS_A2_CPP_APICharacter::Fire()

{
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	// Set Spawn in front of the camera
	ProjectileSpawner.Set(70.0f, 0.0f, 30.0f);
	FVector Spawner = CameraLocation + FTransform(CameraRotation).TransformVector(ProjectileSpawner);

	// Skew the aim to be slightly upwards.
	FRotator Rotation = CameraRotation;
	Rotation.Pitch += 10.0f;

	// Spawn the projectile in the World at the Spawner.
	UWorld* World = GetWorld();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();


	AMyPaintBall* Projectile = World->SpawnActor<AMyPaintBall>(AMyPaintBall::StaticClass(), Spawner, Rotation, SpawnParameters);




}




void ATPS_A2_CPP_APICharacter::Life(int LifeUpdate)
{
	if (vie + LifeUpdate <= vieMax && vie + LifeUpdate >= 0)
		vie += LifeUpdate;

	GLog->Log("Ta vie actuel espece de gros caca : " + FString::FromInt(GetLife()));

	if (vie + LifeUpdate <= 0)
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));

	//il faut mettre le truc du reload de level la ---------------------------------------------------------------------------------



}

int ATPS_A2_CPP_APICharacter::GetLife()
{
	return vie;
}







void ATPS_A2_CPP_APICharacter::Interact() 
{
	TArray<AActor*>inRangeItems;
	collectionRange->GetOverlappingActors(inRangeItems);

	for (int i = 0; i < inRangeItems.Num(); i++) 
	{
		AMyPickUp* const testItem = Cast<AMyPickUp>(inRangeItems[i]);
		if (testItem && !testItem->IsPendingKill() && testItem->GetActive()) 
		{
			testItem->Interacted();
			if (wielded) 
			{
				wielded->SetActorHiddenInGame(false);
			}

		}

	}
}



//void ATPS_A2_CPP_APICharacter::OnDeath()
//{
//	bIsDead = false;
//
//	if (RestartTimerHandle.IsValid())
//	{
//		GetWorldTimerManager().ClearTimer(RestartTimerHandle);
//	}
//
//	
//	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));
//}

void ATPS_A2_CPP_APICharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	if (wielded) 
	{
		wielded->SetActorHiddenInGame(true);
	}
}
void ATPS_A2_CPP_APICharacter::OnStartRun()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ATPS_A2_CPP_APICharacter::OnStopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void ATPS_A2_CPP_APICharacter::OnResetVR()
{
	// If TPS_A2_CPP_API is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in TPS_A2_CPP_API.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATPS_A2_CPP_APICharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ATPS_A2_CPP_APICharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}



void ATPS_A2_CPP_APICharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATPS_A2_CPP_APICharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}



void ATPS_A2_CPP_APICharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATPS_A2_CPP_APICharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
