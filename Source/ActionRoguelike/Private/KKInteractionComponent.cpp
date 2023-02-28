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
{	//FCollisionObjectQueryParams ������һϵ�п��ܻ��õ��Ĳ���
	FCollisionObjectQueryParams ObjectQueryParams;
	//��ѯ�����еĶ�̬����
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic); 

	FVector EyeLocation;
	FRotator EyeRotaion;
	// actor component һ���Ǹ�������������ϣ�GetOwner���ǻ�ȡ�����ŵ�Actor������Ŀ��KKCharactor��
	AActor* Owner = GetOwner(); 
	//����Owner���۾�����ֵ����ʼ������������
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotaion); 
	//��������ߵĳ���
	FVector End = EyeLocation + (EyeRotaion.Vector() * 1000); 
	//��ѯ�Ľ��
	FHitResult Hit; 

	/*
	������ĳЩ���߽��н�������������ʱ�����Ҫʹ�����߼��ȥ�������Ƿ��ܺ͵��߽��н�����
	LineTraceSingleByObjectType��ͨ��ObjectType�����м���
	LineTraceSingleByChannel��ͨ��Channel�����м���
	*/
	GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams); 

	/*
	��������������߼��ļ�⣬�������뽫�Լ���������жϣ�Ҳ����Hit������
	*/
	//�����ײ��������actor����ô���Դӽ��Hit�н����ȡ
	AActor* HitActor = Hit.GetActor();
	//����HitActor�Ƿ���ڽ����߼��ж�
	if (HitActor)
	{
		//�жϱ���⵽��actor�Ƿ���ʵ�ֽӿڣ�Ҳ�����ж�chest�Ƿ�ʵ��GameplayINTF��
		if (HitActor->Implements<UKKGameplayINTF>())
		{
			//ʵ���˽ӿڣ����ڿ��Ե��ý����ĺ�����
			APawn* MyPawn = Cast<APawn>(Owner);		//����ת��
			IKKGameplayINTF::Execute_Interact(HitActor, MyPawn);	//ִ��KKChest��Interact_Implementation����
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

