// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SMCharacter.generated.h"


UCLASS()
class TESTING_API ASMCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASMCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* SMCapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCharacterMovementComponent* SMCharacterMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = cable)
	class UCableComponent* rope;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ABaseWeapon* weapon;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseWeapon> HandgunClass;
	class ABaseWeapon* handgun;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseWeapon> RocketClass;
	class ABaseWeapon* rocket_launcher;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//On hit, if space held, jump
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp,
		bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit) override;

	void SwitchWeapon();

	void Fire();

	void Reload();
		
	void RopeStuff(float DeltaTime);
	void FireRope();
	void PullRope();
	void DetachRope();

	//Jumping
	void StartJump();
	void StopJump();

	//Input
	UPROPERTY(EditAnywhere)
	float fAxis;
	UPROPERTY(EditAnywhere)
	float rAxis;

	//Source Movement
	UPROPERTY(EditAnywhere)
	float AirAcceleration;
	UPROPERTY(EditAnywhere)
	float GroundAcceleration;
	UPROPERTY(EditAnywhere)
	float MaxAirSpeedIncrease;
	int TicksOnGround;	
	bool spaceHold;

	FVector MovementStuff(float DeltaTime, float _fAxis, float _rAxis);
	UFUNCTION(Client, Reliable) void MovementStuff_Client();
	UFUNCTION(BlueprintCallable) FVector CreateAccelerationVector(float _fAxis, float _rAxis);
	FVector GetNextFrameVelocity(FVector AccelVector, float DeltaTime);

	UFUNCTION(Server, Reliable)
	void SetVelocity_Server(FVector vel, float DeltaTime);

	UFUNCTION(Client, Reliable)
	void SetVelocity_Client(FVector vel, float DeltaTime);

	UFUNCTION(Server, Reliable)
	void ReplicateMovementPlease(float dTime, float _fAxis, float _rAxis);

	//Swinging
	UPROPERTY(EditAnywhere)
	float MaxRopeDistance;
	UPROPERTY(EditAnywhere)
	float RopePullSpeed;
	UPROPERTY(EditAnywhere)
	bool WidowGrapple;
	bool ropeFired;
	bool ropeAttached;
	FHitResult ropeTarget;
	//ASMRope rope;

	
};
