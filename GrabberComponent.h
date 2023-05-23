#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONRAIDER_API UGrabberComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Function that returns a HandelComponent type pointer
	UPhysicsHandleComponent* GetPhysicsHandle();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Grab function called in blueprint
	UFUNCTION(BlueprintCallable)
	void Grab();

	//Release function called in blueprint
	UFUNCTION(BlueprintCallable)
	void Release();

private:
	//Defines the distance the player can grab an object
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400;
	
	//Defines the radious of the sphere collision
	UPROPERTY(EditAnywhere)
	float GrabRadious = 100;

	//Returns if the collision sphere hit with an object or not
	bool GrabObjectInReach(FHitResult& HitResult) const;

};
