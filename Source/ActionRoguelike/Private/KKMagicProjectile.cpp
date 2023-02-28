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
	//SphereComp->SetCollisionObjectType(ECC_WorldStatic);	//������ײ���ͣ��ƶ�ʱ����Ϊ�������ͣ�
	//SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);	//�������е���ײͨ����ִ���β�
	//SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);	//�����ض�����ײͨ����ִ���β�
	SphereComp->SetCollisionProfileName("Projectile"); //�Զ�����ײԤ�裬Ҳ������һ��
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AKKMagicProjectile::OnActorOverlap);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;	//����ÿһ֡�������ٶȽ�����ת
	MovementComp->bInitialVelocityInLocalSpace = true;	//�ڿյ�����
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
	//���OtherActor���ڣ���ô���������ص�
	if (OtherActor) {
		//��ȡ����ײ�������actor�����һ����˵ֻ�н�ɫ�͵��˻ᱻ����������
		UKKAttributeComponent* AttributeComp = Cast<UKKAttributeComponent>(OtherActor->GetComponentByClass(UKKAttributeComponent::StaticClass()));
		//�ж��ǲ��������˽�ɫ���ߵ���
		if (AttributeComp) {
			AttributeComp->ApplyHealthChange(-1.0f);
			Destroy(); //��ֹ����ж�
		}
	}
}

