// Fill out your copyright notice in the Description page of Project Settings.


#include "KKExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

// Sets default values
AKKExplosiveBarrel::AKKExplosiveBarrel()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
	MeshComp->SetSimulatePhysics(true); //ģ������Ҳ��������ͼ������

	RadiaForceComp = CreateDefaultSubobject<URadialForceComponent>("RadiaForceComp");
	RadiaForceComp->SetupAttachment(MeshComp);

	// Leaving this on applies small constant force via component 'tick' (Optional)
	//RadiaForceComp->SetAutoActivate(false);

	RadiaForceComp->Radius = 750.0f;
	RadiaForceComp->ImpulseStrength = 1000.0f;
	RadiaForceComp->bImpulseVelChange = true; //�����������㶨�ٶ�

	// Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic
	RadiaForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AKKExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this, &AKKExplosiveBarrel::OnActorHit);
}

void AKKExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadiaForceComp->FireImpulse();
	//��־���ԣ��β��б�˳���ǣ���־���ͣ���־������־���ݡ�����GetNameSafe�Ϳ��Բ��п�
	UE_LOG(LogTemp, Log, TEXT("OtherActor is %s, at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	UE_LOG(LogTemp, Warning, TEXT("Warning Test"));
	//DrawDebugString ����ֱ���������д�ӡ���ı����ݣ��βξ����ı��ĸ������
	FString CombStr = FString::Printf(TEXT("Hit at %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombStr, nullptr, FColor::Yellow, 2.0f, false);
}

// Called when the game starts or when spawned
void AKKExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKKExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

