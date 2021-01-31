// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "AIController.h"

#include "PlayerCharacter.h"
#include "EnemyAIController.h"

#include "Enemy.generated.h"

UCLASS()
class SAVETHETEDDY_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APlayerCharacter* Player;
	AEnemyAIController* EnemyAIController;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UAudioComponent* AudioComp;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CaughtPlayer();

	FVector orientation;
};
