// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "ABCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));

	RootComponent = Weapon;

	Weapon->SetCollisionProfileName(TEXT("Item"));

	// Weapon->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WEAPON (TEXT("/Game/A_ShootingGame/Mesh/Weapon/FPS_Weapon_Bundle/Weapons/Meshes/Ka47/SM_KA47_X.SM_KA47_X"));
	if (SM_WEAPON.Succeeded())
	{
		Weapon->SetStaticMesh(SM_WEAPON.Object); 
	}
	
	

}



// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Weapon->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnCharacterOverlap);
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABLOG_S(Warning);

	// 캐릭터 오버랩시 처리될 로직
	if (GetWorld()->GetFirstPlayerController()->GetPawn() == OtherActor)
	{
		auto Character = Cast<AABCharacter>(OtherActor);

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Overlap Character!!"));

		

	}
	

	
	
}

