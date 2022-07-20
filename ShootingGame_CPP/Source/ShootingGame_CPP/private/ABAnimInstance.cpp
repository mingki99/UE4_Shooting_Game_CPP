// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	Speed = 0.0f;
	Direction = 0.0f;
	IsInAir = false;
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn)) return;
	
	
	Speed = Pawn->GetVelocity().Size();

	Direction = CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
}