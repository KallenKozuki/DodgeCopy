// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	//包含一套来自UE内核的编程环境的普遍存在类（包FString、FName、TArray等）
#include "GameFramework/Character.h"
#include "KKInteractionComponent.h"
#include "KKCharactor.generated.h"	//头文件必须在generated文件上方

class UCameraComponent;
class USpringArmComponent;
class UKKInteractionComponent;
class UAnimMontage;
class UKKAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API AKKCharactor : public ACharacter
{
	GENERATED_BODY()	//宏，需要保持在该类的第一行

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

public:
	// Sets default values for this character's properties
	AKKCharactor();

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;	//摇臂

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;	//相机

	UPROPERTY(VisibleAnywhere)
	UKKInteractionComponent* InteractionComp;	//交互组件

	UPROPERTY(EditAnywhere, Category = "Attack") 
	UAnimMontage* PrimaryAttackAnim;	//使用montage实现攻击动画

	UPROPERTY(EditAnywhere, Category = "Attack")	//出招延迟
	float AttackDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") //角色属性
	UKKAttributeComponent* AttributeComp;



	FTimerHandle TimerHandle_PrimaryAttack; //FTimerHandle是可用于区分具有相同委托的计时器的唯一句柄。

	void MoveForward(float value);		//前进后退
	void MoveRight(float value);		//左右移动
	void PrimaryAttack();				//普通攻击+播放相应的动画
	void PrimaryInteract();				//交互
	void PrimaryAttack_TimeElapsed();	//发射普攻粒子


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
