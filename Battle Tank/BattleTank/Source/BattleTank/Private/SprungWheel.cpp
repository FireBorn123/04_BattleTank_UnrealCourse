// Copyright Trevor Randall

#include "SprungWheel.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "Tank.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	SuspensionSpring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("SuspensionSpring"));
	SetRootComponent(SuspensionSpring);

	TankAxle = CreateDefaultSubobject<USphereComponent>(FName("TankAxle"));
	TankAxle->AttachToComponent(SuspensionSpring, FAttachmentTransformRules::KeepRelativeTransform);
	TankAxle->SetSimulatePhysics(true);

	WheelRotator = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("WheelRotator"));
	WheelRotator->AttachToComponent(TankAxle, FAttachmentTransformRules::KeepRelativeTransform);

	TankWheel = CreateDefaultSubobject<USphereComponent>(FName("TankWheel"));
	TankWheel->AttachToComponent(TankAxle, FAttachmentTransformRules::KeepRelativeTransform);
	TankWheel->SetSimulatePhysics(true);


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

	TankWheel->SetNotifyRigidBodyCollision(true);
	TankWheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetupConstraints();
}



void ASprungWheel::SetupConstraints()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());

	if (!BodyRoot) { return; }
	SuspensionSpring->SetConstrainedComponents(BodyRoot, NAME_None, TankAxle, NAME_None);
	WheelRotator->SetConstrainedComponents(TankAxle, NAME_None, TankWheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{ 
		TotalForceMagnitudeThisFrame = 0;
	}
	
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	TankWheel->AddForce(TankAxle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}