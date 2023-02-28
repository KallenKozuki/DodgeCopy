// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	//����һ������UE�ں˵ı�̻������ձ�����ࣨ��FString��FName��TArray�ȣ�
#include "GameFramework/Character.h"
#include "KKInteractionComponent.h"
#include "KKCharactor.generated.h"	//ͷ�ļ�������generated�ļ��Ϸ�

class UCameraComponent;
class USpringArmComponent;
class UKKInteractionComponent;
class UAnimMontage;
class UKKAttributeComponent;

UCLASS()
class ACTIONROGUELIKE_API AKKCharactor : public ACharacter
{
	GENERATED_BODY()	//�꣬��Ҫ�����ڸ���ĵ�һ��

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

public:
	// Sets default values for this character's properties
	AKKCharactor();

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;	//ҡ��

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;	//���

	UPROPERTY(VisibleAnywhere)
	UKKInteractionComponent* InteractionComp;	//�������

	UPROPERTY(EditAnywhere, Category = "Attack") 
	UAnimMontage* PrimaryAttackAnim;	//ʹ��montageʵ�ֹ�������

	UPROPERTY(EditAnywhere, Category = "Attack")	//�����ӳ�
	float AttackDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components") //��ɫ����
	UKKAttributeComponent* AttributeComp;



	FTimerHandle TimerHandle_PrimaryAttack; //FTimerHandle�ǿ��������־�����ͬί�еļ�ʱ����Ψһ�����

	void MoveForward(float value);		//ǰ������
	void MoveRight(float value);		//�����ƶ�
	void PrimaryAttack();				//��ͨ����+������Ӧ�Ķ���
	void PrimaryInteract();				//����
	void PrimaryAttack_TimeElapsed();	//�����չ�����


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
