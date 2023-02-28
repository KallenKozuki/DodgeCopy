// Fill out your copyright notice in the Description page of Project Settings.


#include "KKInteractionComponent.h"
#include "KKGameplayINTF.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UKKInteractionComponent::UKKInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UKKInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UKKInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UKKInteractionComponent::PrimaryInteract()
{	//FCollisionObjectQueryParams 包含了一系列可能会用到的参数
	FCollisionObjectQueryParams ObjectQueryParams;
	//查询场景中的动态对象
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic); 

	FVector EyeLocation;
	FRotator EyeRotaion;
	// actor component 一般是附着在其他组件上，GetOwner就是获取被附着的Actor（本项目是KKCharactor）
	AActor* Owner = GetOwner(); 
	//根据Owner的眼睛的数值，初始化这两个变量
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotaion); 
	//画出检测线的长度
	FVector End = EyeLocation + (EyeRotaion.Vector() * 1000); 
	//查询的结果
	FHitResult Hit; 

	/*
	遇到和某些道具进行交互的情况，这个时候就需要使用射线检测去检测玩家是否能和道具进行交互：
	LineTraceSingleByObjectType是通过ObjectType来进行检测的
	LineTraceSingleByChannel是通过Channel来进行检测的
	*/
	GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams); 

	/*
	上述代码完成了逻辑的检测，下述代码将对检测结果进行判断（也就是Hit变量）
	*/
	//如果碰撞到了其他actor，那么可以从结果Hit中将其获取
	AActor* HitActor = Hit.GetActor();
	//根据HitActor是否存在进行逻辑判断
	if (HitActor)
	{
		//判断被检测到的actor是否有实现接口（也就是判断chest是否实现GameplayINTF）
		if (HitActor->Implements<UKKGameplayINTF>())
		{
			//实现了接口，现在可以调用交互的函数了
			APawn* MyPawn = Cast<APawn>(Owner);		//类型转换
			IKKGameplayINTF::Execute_Interact(HitActor, MyPawn);	//执行KKChest的Interact_Implementation函数
			DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Yellow, false, 3);
		}
		else
		{
			DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Red, false, 3);
		}
	}
	if (HitActor) return true;
	return false;
}

