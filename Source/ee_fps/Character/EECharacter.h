// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EECharacter.generated.h"

class UInputMappingContext;
class UCameraComponent;
struct FInputActionValue;
class UInputAction;
class UInputComponent;

UCLASS()
class EE_FPS_API AEECharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AEECharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * Components
	 */


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* FPCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* EEFPV;

	/*
	 * Input Mapping Context and Actions
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	void Move(const FInputActionValue& Value);

	void Looking(const FInputActionValue& Value);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
