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

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp"); //括号内初始化名字
	SpringArmComp->SetupAttachment(RootComponent); //连接到根组件
	SpringArmComp->bUsePawnControlRotation = true;	//可以通过控制器旋转SpringArmComp（也就是镜头）

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);	//连接到SpringArmComp

	InteractionComp = CreateDefaultSubobject<UKKInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<UKKAttributeComponent>("AttributeComp");

	AttackDelay = 0.16f;

	GetCharacterMovement()->bOrientRotationToMovement = true;	//让Pawn跟随控制器（镜头）旋转的方向进行移动
	bUseControllerRotationYaw = false;	//Pawn 对象不会因为控制器旋转而旋转
	
}


void AKKCharactor::MoveForward(float value)
{	
	FRotator ControllerRot = GetControlRotation(); //获取控制器的旋转角度，有三个维度，我们只需要在水平（Yaw）方向上让Pawn旋转
	ControllerRot.Roll = 0.0f;	//控制器另外两个维度的旋转不要考虑，因此设置为0
	ControllerRot.Pitch = 0.0f;
	AddMovementInput(ControllerRot.Vector(), value);	//GetActorForwardVector()不在是真正的方向，而是旋转量所面对的方向
}

void AKKCharactor::MoveRight(float value)
{
	FRotator ControllerRot = GetControlRotation();
	ControllerRot.Roll = 0.0f;
	ControllerRot.Pitch = 0.0f;
	// X 前进	红色
	// Y 右		绿色
	// Z 上		蓝
	FVector RightVector = FRotationMatrix(ControllerRot).GetScaledAxis(EAxis::Y); //获取向右的矢量
	AddMovementInput(RightVector, value);
}

void AKKCharactor::PrimaryAttack()
{	
	PlayAnimMontage(PrimaryAttackAnim); //播放动画（需要在虚幻编辑器中选定要播放的动画）
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

	//用于获取输入，按照轴的方式输入，接受来自名为"MoveForward"的输入，移动this角色，调用MoveForward函数来移动
	PlayerInputComponent->BindAxis("MoveForward", this, &AKKCharactor::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKKCharactor::MoveRight);

	//移动视角: Yaw-水平	Pitch-垂直	Roll-翻滚自身，这些函数由引擎实现，直接调用即可
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
	//GetSocketLocation: 获取socket或者骨头的位置（socket就是骨骼体的构造单元）
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	//FTransform: 由缩放、旋转(作为四元数)和平移组成的变换。
	//GetControlRotation() 沿摄像机方向发射   GetActorRotation() 沿角色面对的方向发射
	FTransform SpawnTM = FTransform(GetActorRotation(), HandLocation * 1.05);

	//actor 的生成参数
	FActorSpawnParameters SpawnParams;
	//制定actor的生成策略，考虑不同碰撞时都会如何生成（此处设置为总是生成）
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}