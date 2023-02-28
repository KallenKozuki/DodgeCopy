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
	MeshComp->SetSimulatePhysics(true); //模拟物理，也可以在蓝图中设置

	RadiaForceComp = CreateDefaultSubobject<URadialForceComponent>("RadiaForceComp");
	RadiaForceComp->SetupAttachment(MeshComp);

	// Leaving this on applies small constant force via component 'tick' (Optional)
	//RadiaForceComp->SetAutoActivate(false);

	RadiaForceComp->Radius = 750.0f;
	RadiaForceComp->ImpulseStrength = 1000.0f;
	RadiaForceComp->bImpulseVelChange = true; //无视质量，恒定速度

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
	//日志测试，形参列表按顺序是：日志类型，日志级别，日志内容。用了GetNameSafe就可以不判空
	UE_LOG(LogTemp, Log, TEXT("OtherActor is %s, at game time %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);
	UE_LOG(LogTemp, Warning, TEXT("Warning Test"));
	//DrawDebugString 可以直接在世界中打印出文本内容，形参就是文本的各项参数
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

