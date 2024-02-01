// Fill out your copyright notice in the Description page of Project Settings.


#include "ee_fps/Character/EECharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEECharacter::AEECharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*Camera Component*/
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	FPCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPCameraComponent->bUsePawnControlRotation = true;

	/*Skeletal Mesh Component*/
	EEFPV = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPSMesh"));
	EEFPV->SetupAttachment(FPCameraComponent);
}

void AEECharacter::Move(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Emerald, TEXT("Triggering the move function"));

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);

	}
}

void AEECharacter::Looking(const FInputActionValue& Value)
{
	FVector2D LookingVector = Value.Get<FVector2D>();

	if (Controller !=nullptr)
	{
		AddControllerYawInput(LookingVector.X);
		AddControllerPitchInput(LookingVector.Y);
	}
}

// Called when the game starts or when spawned
void AEECharacter::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSChracther"));

	//Adding the input mapping context

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(IMC, 0);
			}
	}
}


// Called every frame
void AEECharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEECharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEECharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEECharacter::Looking);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	}
}

