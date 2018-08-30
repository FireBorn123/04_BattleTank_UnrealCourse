// Copyright Trevor Randall

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Spring")
	USphereComponent* TankWheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Spring")
	USphereComponent* TankAxle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Spring")
	UPhysicsConstraintComponent* WheelRotator = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Spring")
	UPhysicsConstraintComponent* SuspensionSpring = nullptr;

	

private:
	// Sets default values for this actor's properties
	ASprungWheel();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void ApplyForce();
	
	void SetupConstraints();

	float DefaultSpringStrength = 2500.0;

	float DefaultVelocityStrength = 500.0;

	float TotalForceMagnitudeThisFrame = 0;
	
	
};
