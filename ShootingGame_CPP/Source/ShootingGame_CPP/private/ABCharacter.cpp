// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"
#include "ABPlayercontroller.h"
#include "ABAnimInstance.h"

#include "Weapon.h"


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
	// ȸ�� �ӵ�
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
	
	

	FActorSpawnParameters SpawnParmeters;

	SpawnParmeters.Owner = this;

	// ������ ĳ���Ͱ� ���ָ� �ȵȴ�, ���̳�, �������� ��ȯ���ִ°� �ڿ�������.
	
	

	auto GunWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector , FRotator::ZeroRotator, SpawnParmeters);
	ABCHECK(nullptr != GunWeapon);

	GunWeapon->SetActorEnableCollision(false);
	

	FName GunWeaponSoket(TEXT("WeponSocket"));

	
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true);

	GunWeapon->AttachToComponent(GetMesh(),  AttachmentTransformRules, GunWeaponSoket);

	
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

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);

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

