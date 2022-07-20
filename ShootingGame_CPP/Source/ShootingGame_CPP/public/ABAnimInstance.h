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
	// virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Locomotion, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Locomotion, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Locomotion, Meta = (AllowPrivateAccess = true))
	float Direction;
};
