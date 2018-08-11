// Copyright Trevor Randall

#include "SprungWheel.h"
#include "Tank.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SuspensionSpring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SuspensionSpring"));
	SetRootComponent(SuspensionSpring);

	TankMass = CreateDefaultSubobject<UStaticMeshComponent>(FName("TankMass"));
	TankMass->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TankMass->SetSimulatePhysics(true);

	TankWheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("TankWheel"));
	TankWheel->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TankWheel->SetSimulatePhysics(true);



	// Set Component Attachments
	SuspensionSpring->ComponentName1.ComponentName = FName("TankMass");
	SuspensionSpring->ComponentName2.ComponentName = FName("TankWheel");

	// Set linear limit freedom
	SuspensionSpring->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	SuspensionSpring->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	SuspensionSpring->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.f);

	// Set angular limit freedom
	SuspensionSpring->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	SuspensionSpring->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	SuspensionSpring->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.f);

	// Set 
	SuspensionSpring->SetLinearPositionDrive(false, false, true);
	SuspensionSpring->SetLinearVelocityDrive(false, false, true);
	SuspensionSpring->SetLinearDriveParams(DefaultSpringStrength, DefaultVelocityStrength, 0.f);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Null"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Null"));
	}
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

