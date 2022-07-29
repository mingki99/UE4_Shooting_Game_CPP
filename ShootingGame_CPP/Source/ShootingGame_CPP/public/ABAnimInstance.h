// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGame_CPP.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTINGGAME_CPP_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UABAnimInstance();

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void SetEquip(bool IsEquip);

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Locomotion, Meta = (AllowPrivateAccess = true))
	float fMoveForWardValueX;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Locomotion, Meta = (AllowPrivateAccess = true))
	float fMoveRightValueY;

private:
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Locomotion, Meta = (AllowPrivateAccess = true))
	float fSpeed;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Locomotion, Meta = (AllowPrivateAccess = true))
	float fDirection;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Locomotion, Meta = (AllowPrivateAccess = true))
	bool bIsInAir;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Locomotion, Meta = (AllowPrivateAccess = true))
	bool bIsEquip;



	
};
