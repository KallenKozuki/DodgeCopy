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
	
	//如果在 character 类中创建属性，那么就会导致其越来越臃肿，解决方法是用actor组件来实现
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(float Delta); //用于修改生命值

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const; //存活判断

	UPROPERTY(BlueprintAssignable) //只能与广播交互
	//FOnHealthChanged OnHealthChanged;
		
};
