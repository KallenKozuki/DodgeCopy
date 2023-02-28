// Fill out your copyright notice in the Description page of Project Settings.


#include "KKCharactor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KKAttributeComponent.h"

// Sets default values
AKKCharactor::AKKCharactor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp"); //�����ڳ�ʼ������
	SpringArmComp->SetupAttachment(RootComponent); //���ӵ������
	SpringArmComp->bUsePawnControlRotation = true;	//����ͨ����������תSpringArmComp��Ҳ���Ǿ�ͷ��

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);	//���ӵ�SpringArmComp

	InteractionComp = CreateDefaultSubobject<UKKInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<UKKAttributeComponent>("AttributeComp");

	AttackDelay = 0.16f;

	GetCharacterMovement()->bOrientRotationToMovement = true;	//��Pawn�������������ͷ����ת�ķ�������ƶ�
	bUseControllerRotationYaw = false;	//Pawn ���󲻻���Ϊ��������ת����ת
	
}


void AKKCharactor::MoveForward(float value)
{	
	FRotator ControllerRot = GetControlRotation(); //��ȡ����������ת�Ƕȣ�������ά�ȣ�����ֻ��Ҫ��ˮƽ��Yaw����������Pawn��ת
	ControllerRot.Roll = 0.0f;	//��������������ά�ȵ���ת��Ҫ���ǣ��������Ϊ0
	ControllerRot.Pitch = 0.0f;
	AddMovementInput(ControllerRot.Vector(), value);	//GetActorForwardVector()�����������ķ��򣬶�����ת������Եķ���
}

void AKKCharactor::MoveRight(float value)
{
	FRotator ControllerRot = GetControlRotation();
	ControllerRot.Roll = 0.0f;
	ControllerRot.Pitch = 0.0f;
	// X ǰ��	��ɫ
	// Y ��		��ɫ
	// Z ��		��
	FVector RightVector = FRotationMatrix(ControllerRot).GetScaledAxis(EAxis::Y); //��ȡ���ҵ�ʸ��
	AddMovementInput(RightVector, value);
}

void AKKCharactor::PrimaryAttack()
{	
	PlayAnimMontage(PrimaryAttackAnim); //���Ŷ�������Ҫ����ñ༭����ѡ��Ҫ���ŵĶ�����
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AKKCharactor::PrimaryAttack_TimeElapsed, AttackDelay);
}

// Called when the game starts or when spawned
void AKKCharactor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKKCharactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKKCharactor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//���ڻ�ȡ���룬������ķ�ʽ���룬����������Ϊ"MoveForward"�����룬�ƶ�this��ɫ������MoveForward�������ƶ�
	PlayerInputComponent->BindAxis("MoveForward", this, &AKKCharactor::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKKCharactor::MoveRight);

	//�ƶ��ӽ�: Yaw-ˮƽ	Pitch-��ֱ	Roll-����������Щ����������ʵ�֣�ֱ�ӵ��ü���
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKKCharactor::Jump);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AKKCharactor::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AKKCharactor::PrimaryInteract);


}

void AKKCharactor::PrimaryInteract()
{
	bool FindSomething = InteractionComp->PrimaryInteract();
	if (FindSomething)
	{
		AttributeComp->ApplyHealthChange(20.f);
	}
	
}

void AKKCharactor::PrimaryAttack_TimeElapsed()
{
	//GetSocketLocation: ��ȡsocket���߹�ͷ��λ�ã�socket���ǹ�����Ĺ��쵥Ԫ��
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	//FTransform: �����š���ת(��Ϊ��Ԫ��)��ƽ����ɵı任��
	//GetControlRotation() �������������   GetActorRotation() �ؽ�ɫ��Եķ�����
	FTransform SpawnTM = FTransform(GetActorRotation(), HandLocation * 1.05);

	//actor �����ɲ���
	FActorSpawnParameters SpawnParams;
	//�ƶ�actor�����ɲ��ԣ����ǲ�ͬ��ײʱ����������ɣ��˴�����Ϊ�������ɣ�
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}