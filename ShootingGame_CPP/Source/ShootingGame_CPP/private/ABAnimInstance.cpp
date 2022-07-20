// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	Speed = 0;
	Direction = 0;
	IsInAir = false;
}

//void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
//{
//	Super::NativeUpdateAnimation(DeltaSeconds);
//
//	auto APawn = TryGetPawnOwner();
//	
//	Speed = APawn->GetVelocity().Size();
//
//	Direction = CalculateDirection(APawn->GetVelocity(), APawn->GetActorRotation());
//}