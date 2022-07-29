// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	fSpeed = 0.0f;
	fDirection = 0.0f;
	bIsInAir = false;
	bIsEquip = false;
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;
	
	
	fSpeed = Pawn->GetVelocity().Size();

	fDirection = CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());


	bIsInAir = Pawn->GetMovementComponent()->IsFalling();
}

void UABAnimInstance::SetEquip(bool IsEquip)
{
	bIsEquip = IsEquip;
}