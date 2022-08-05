// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"
#include "ABPlayercontroller.h"
#include "ABAnimInstance.h"

#include "Weapon.h"
#include "DrawDebugHelpers.h"

#include "Engine/EngineTypes.h"

// #include "Components/SpringArm.h"


// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	// WeaponMesh->SetupAttachment(GetCapsuleComponent());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	// 회전 속도
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_MESH(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (SK_MESH.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_MESH.Object);
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> SHOOTING_ANIM(TEXT("/Game/A_ShootingGame/Animation/ANBP_Shooting.ANBP_Shooting_C"));
	if (SHOOTING_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(SHOOTING_ANIM.Class);
	}

	GetCharacterMovement()->JumpZVelocity = 800.0f;


	WeaponClass = AWeapon::StaticClass();

	// FName GunWeaponSoket(TEXT("WeponSocket"));
	/*if (GetMesh()->DoesSocketExist(GunWeaponSoket));
	{
		GunWeaopn = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunWeapon"));
	}*/

}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
	// 생성은 캐릭터가 해주면 안된다, 맵이나, 구조물이 소환해주는게 자연스럽다.



	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
	ABCHECK(nullptr != CurrentWeapon);
	CurrentWeapon->SetActorEnableCollision(false);

	
	FName GunWeaponSoket(TEXT("WeponSocket"));

	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);

	CurrentWeapon->AttachToComponent(GetMesh(),  AttachmentTransformRules, GunWeaponSoket);
	CurrentWeapon->SetOwner(this);
	
}



void AABCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ABAnim = Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());

	ABAnim->SetEquip(true);

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

	// Action
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("ClickedLeft"), EInputEvent::IE_Pressed, this,  &AABCharacter::ClickedLeft);

	// Axis
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AABCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AABCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AABCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AABCharacter::Turn);
	
}

void AABCharacter::MoveForward(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
	ABAnim->fMoveForWardValueX = NewAxisValue;
	// ABLOG(Warning, TEXT("%f"), NewAxisValue);
}

void AABCharacter::MoveRight(float NewAxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
	ABAnim->fMoveRightValueY = NewAxisValue;
}

void AABCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
	
}

void AABCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
	// ABLOG(Warning, TEXT("%f"), NewAxisValue);
}

void AABCharacter::ClickedLeft()
{
	if (nullptr != CurrentWeapon)
	{
		if(ABAnim->GetIs)
		// Weapon socket "Muzzle" 기준 라인트레이스 실행
		FVector WeaponTraceStart = CurrentWeapon->Weapon->GetSocketLocation(TEXT("Muzzle"));
		FVector WeaponTraceEnd = WeaponTraceStart + (CurrentWeapon->Weapon->GetSocketRotation(TEXT("Muzzle")).Vector() * 2000.0f);

		FHitResult HitResult;
		FCollisionObjectQueryParams CollisionObjectQueryParams;

		
		GetWorld()->LineTraceSingleByObjectType(HitResult, WeaponTraceStart, WeaponTraceEnd,
		FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic) | ECC_TO_BITFIELD(ECC_Pawn) | ECC_TO_BITFIELD(ECC_PhysicsBody)), false);

		DrawDebugLine(GetWorld(), WeaponTraceStart, WeaponTraceEnd, FColor::Green, false, 5.0f);

	}
	
}

void AABCharacter::SpawnGunWeapon(Aweapon* Weapon)
{
	
}

void AABCharacter::SetWeapon(AWeapon* Weapon)
{

}


