// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpScareActor.h"

// Sets default values
AJumpScareActor::AJumpScareActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CollisionComp->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	CollisionComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AJumpScareActor::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AJumpScareActor::BeginOverlap);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &AJumpScareActor::EndOverlap);
}

// Called every frame
void AJumpScareActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJumpScareActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Player)
	{
		if (OtherComp->ComponentHasTag(FName("Player")))
		{
			if (hasBeenActivated == false)
			{
				JumpScare();
			}
		}
	}
}

void AJumpScareActor::EndOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AJumpScareActor::JumpScare()
{
	AudioComp->Play(0.0f);
	Player->JumpScared();
	hasBeenActivated = true;
}