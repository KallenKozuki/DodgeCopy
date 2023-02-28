// Fill out your copyright notice in the Description page of Project Settings.


#include "KKAttributeComponent.h"

// Sets default values for this component's properties
UKKAttributeComponent::UKKAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	Health = 100.0f;
	// ...
}


// Called when the game starts
void UKKAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UKKAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UKKAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	//OnHealthChanged.Broadcast(nullptr, this, Health, Delta); //每当血量改变后，执行广播

	if (Health > 100)
	{
		Health = 100.0f;
	}
	else if (Health < 0)
	{
		Health = 0.0f;
	}


	return true;
}

bool UKKAttributeComponent::IsAlive() const
{
	if (Health > 0) return true;
	return false;
}

