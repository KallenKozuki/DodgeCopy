// Fill out your copyright notice in the Description page of Project Settings.


#include "KKMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "KKAttributeComponent.h"

// Sets default values
AKKMagicProjectile::AKKMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//SphereComp->SetCollisionObjectType(ECC_WorldStatic);	//设置碰撞类型（移动时被视为何种类型）
	//SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);	//对于所有的碰撞通道，执行形参
	//SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);	//对于特定的碰撞通道，执行形参
	SphereComp->SetCollisionProfileName("Projectile"); //自定义碰撞预设，也是最方便的一个
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AKKMagicProjectile::OnActorOverlap);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;	//物体每一帧都根据速度进行旋转
	MovementComp->bInitialVelocityInLocalSpace = true;	//在空地生成
}

// Called when the game starts or when spawned
void AKKMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKKMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKKMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//如果OtherActor存在，那么代表发生了重叠
	if (OtherActor) {
		//获取被碰撞的物体的actor组件，一般来说只有角色和敌人会被赋予这个组件
		UKKAttributeComponent* AttributeComp = Cast<UKKAttributeComponent>(OtherActor->GetComponentByClass(UKKAttributeComponent::StaticClass()));
		//判断是不是碰到了角色或者敌人
		if (AttributeComp) {
			AttributeComp->ApplyHealthChange(-1.0f);
			Destroy(); //防止多次判断
		}
	}
}

