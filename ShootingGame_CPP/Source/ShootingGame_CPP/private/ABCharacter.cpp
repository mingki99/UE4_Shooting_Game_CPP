// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"

// #include "Components/SpringArm.h"


// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MESH(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (SK_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MESH.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> SHOOTING_ANIM(TEXT("/Game/A_ShootingGame/Animation/ANBP_Shooting.ANBP_Shooting_C"));
	if (SHOOTING_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(SHOOTING_ANIM.Class);
	}

}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AABCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AABCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AABCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Trun"), this, &AABCharacter::Turn);


}

void AABCharacter::MoveForward(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
	// ABLOG(Warning, TEXT("%f"), NewAxisValue);
}

void AABCharacter::MoveRight(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
	
}


void AABCharacter::UpDown(float NewAxisValue)
{
	
}


void AABCharacter::LookUp(float NewAxisValue)
{
	
}

void AABCharacter::Turn(float NewAxisValue)
{
	
}	

