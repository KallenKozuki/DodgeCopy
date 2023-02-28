// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KKAttributeComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, AActor*, InstigatorActor, UKKAttributeComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UKKAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKKAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	//����� character ���д������ԣ���ô�ͻᵼ����Խ��Խӷ�ף������������actor�����ʵ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta); //�����޸�����ֵ

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const; //����ж�

	UPROPERTY(BlueprintAssignable) //ֻ����㲥����
	//FOnHealthChanged OnHealthChanged;
		
};
