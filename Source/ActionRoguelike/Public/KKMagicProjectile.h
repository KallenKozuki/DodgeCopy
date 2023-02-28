// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KKMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API AKKMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AKKMagicProjectile();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USphereComponent* SphereComp;	//������ײ�����

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UProjectileMovementComponent* MovementComp;	//��Ͷ����һ���ٶȣ����ٶȵķ���ǰ��

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UParticleSystemComponent* EffectComp;	//����ϵͳ����Ч

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
