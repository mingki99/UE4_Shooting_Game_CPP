// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));

	RootComponent = Weapon;


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

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

