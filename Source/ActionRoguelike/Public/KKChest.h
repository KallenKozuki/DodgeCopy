// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KKGameplayINTF.h"
#include "KKChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API AKKChest : public AActor, public IKKGameplayINTF
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn); //13�д��̳нӿڣ����������ӿ�Ҫʵ�ֵ�����
	
public:	
	// Sets default values for this actor's properties
	AKKChest();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* LidMesh;	//����ĸ���

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;	//���䱾��

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float RotatePitch;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
