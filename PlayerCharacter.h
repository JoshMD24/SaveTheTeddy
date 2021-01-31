// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"

#include "Kismet/GameplayStatics.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class SAVETHETEDDY_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Collision
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		 UAudioComponent* AudioComp;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//Gameplay
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int heartRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isCaught;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasHadHeartAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasPickedUpTeddy;

	UFUNCTION(BlueprintCallable)
		void JumpScared();
	UFUNCTION(BlueprintCallable)
		void HeartAttack();

	FTimerHandle HeartRateTimer;

	void CalmDown();
	void Caught();
	void PickupTeddy();
};