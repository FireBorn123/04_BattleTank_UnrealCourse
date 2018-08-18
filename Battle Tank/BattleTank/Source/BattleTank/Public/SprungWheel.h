// Copyright Trevor Randall

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Spring")
	UStaticMeshComponent* TankWheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Spring")
	UPhysicsConstraintComponent* SuspensionSpring = nullptr;

private:
	// Sets default values for this actor's properties
	ASprungWheel();

	void SetupConstraints();

	float DefaultSpringStrength = 2500.0;

	float DefaultVelocityStrength = 500.0;


	
	
};
