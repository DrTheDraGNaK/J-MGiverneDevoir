// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Animation/SkeletalMeshActor.h"
#include "MyPickUp.h"
#include "MyPaintBall.h"
#include "TPS_A2_CPP_APICharacter.generated.h"




UCLASS(config=Game)
class ATPS_A2_CPP_APICharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	

	




public:
	ATPS_A2_CPP_APICharacter();

	

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category=Speed)
		float WalkSpeed = 50.f;

	UPROPERTY(EditAnywhere, Category = Speed)
		float RunSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = Vie, BlueprintReadWrite)
		int vie = 100;

	UPROPERTY(EditAnywhere, Category = Vie, BlueprintReadWrite)
		 int vieMax = 100;

	UPROPERTY(EditAnywhere, Category = Fire)
		USceneComponent* ProjectileSpawner;

	UPROPERTY(EditDefaultsOnly, Category = Fire)
		TSubclassOf<AMyPaintBall> Bullet;

protected:

	void Fire();

	


	void BeginPlay() override;


	UFUNCTION()
		void OnStartRun();

	UFUNCTION()
		void OnStopRun();

	

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:

	///** Projectile class to spawn */
	//UPROPERTY(EditDefaultsOnly, Category = Projectile)
	//	TSubclassOf<class AMyPaintBall> ProjectileClass;

	


	


	UFUNCTION()
		int GetLife();

	UFUNCTION(BlueprintCallable)
		void Life(int LifeUpdate);


	





	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


private:

	void Interact();

	UPROPERTY(EditAnywhere, Category = "Pickup", meta = (AllowPrivateAccess = true))
		USphereComponent* collectionRange;

	UPROPERTY(EditAnywhere, Category = "Pickup")
		ASkeletalMeshActor* wielded;







};

