// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "PlayerCharacter.h"

#include "JumpScareActor.generated.h"

UCLASS()
class SAVETHETEDDY_API AJumpScareActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpScareActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APlayerCharacter* Player;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UAudioComponent* AudioComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UBoxComponent* CollisionComp;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hasBeenActivated;

	UFUNCTION(BlueprintCallable)
		void JumpScare();
};
