// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CollisionComp->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	CollisionComp->SetupAttachment(RootComponent);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::BeginOverlap);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::EndOverlap);

	GetWorldTimerManager().SetTimer(HeartRateTimer, this, &APlayerCharacter::CalmDown, 0.33, true);

	heartRate = 50;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName("Spider")))
	{
		Caught();
	}
	if (OtherActor->ActorHasTag(FName("Teddy")))
	{
		PickupTeddy();
	}
}

void APlayerCharacter::EndOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void APlayerCharacter::JumpScared()
{
	heartRate = heartRate + 100;

	if (heartRate >= 250)
	{
		HeartAttack();
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(heartRate));
}

void APlayerCharacter::HeartAttack()
{
	GetCharacterMovement()->MaxWalkSpeed = 0;
	hasHadHeartAttack = true;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
		PlayerController->SetInputMode(FInputModeUIOnly());
	}
}
void APlayerCharacter::CalmDown()
{
	if (heartRate > 50)
	{
		heartRate--;
	}
}

void APlayerCharacter::Caught()
{
	GetCharacterMovement()->MaxWalkSpeed = 0;
	isCaught = true;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
		PlayerController->SetInputMode(FInputModeUIOnly());
	}
}
void APlayerCharacter::PickupTeddy()
{
	hasPickedUpTeddy = true;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
		PlayerController->SetInputMode(FInputModeUIOnly());

		GetCharacterMovement()->MaxWalkSpeed = 0;
	}
}
//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(XpNeededForWoodcuttingLevel));