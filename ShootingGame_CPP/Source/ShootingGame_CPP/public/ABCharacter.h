// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame_CPP.h"
#include "GameFramework/Character.h"
#include "ABCharacter.generated.h"

UCLASS()
class SHOOTINGGAME_CPP_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;

	/*UPROPERTY(VisibleAnyWhere, Category = Weapon)
	class UStaticMeshComponent* WeaponMesh;*/

	

private:
	// InputComponent
	
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);


	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	void ClickedLeft();

	void SpawnGunWeapon(class Aweapon* Weapon);
	void SetWeapon(class AWeapon* Weapon);

protected:
	
	UPROPERTY()
	class UABAnimInstance* ABAnim;

	UPROPERTY(BlueprintReadWrite, Category = Weapon)
	class AWeapon* CurrentWeapon;

public:

	UPROPERTY(EditInstanceOnly, Category = Weapon)
	TSubclassOf<class AWeapon> WeaponClass;


	// UPROPERTY()
};
