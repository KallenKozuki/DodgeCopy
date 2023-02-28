// Fill out your copyright notice in the Description page of Project Settings.


#include "KKChest.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
AKKChest::AKKChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	RotatePitch = 100.0f;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKKChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKKChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKKChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(RotatePitch, 0, 0)); //按顺序是Pitch Yaw Roll，次数需要修改的是Pitch，也就是Y
}
