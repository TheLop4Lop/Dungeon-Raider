#include "GrabberComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Pointer that stores the Physics Handle Component on FirstPersonCharacter player
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	//Sets the vector location of the object graabbed by player
	FVector TargetLocation = GetComponentLocation() + (GetForwardVector() * (MaxGrabDistance/2));
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());

}

void UGrabberComponent::Grab()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	//Boolean containing the value of a funtion returning if an object was hit
	FHitResult HitResult;
	bool HasHit = GrabObjectInReach(HitResult);

	if(HasHit)
	{
		//HitResult.ImpactPoint returns a vector when object hit
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Green, false, 5); 

		//UPrimitiveComponent that wakes up the physics on the object
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();

		//Funtion that grabs the object
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent, 
			NAME_None, 
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}

}

void UGrabberComponent::Release()
{	
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	PhysicsHandle->ReleaseComponent();

}

UPhysicsHandleComponent* UGrabberComponent::GetPhysicsHandle()
{
	//Checks if the variable is pointing to nullptr, then returns the HandleComponent
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(Result == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nullptr, check code!"));
	}
	
	return Result;
	
}

bool UGrabberComponent::GrabObjectInReach(FHitResult& HitResult) const
{
	//Vectors that define how long the DebugLine should be
	FVector StartVector = GetComponentLocation();
	FVector EndVector = StartVector + (GetForwardVector() * MaxGrabDistance);

	//Draws a degub line and reach vector in the world
	//DrawDebugLine(GetWorld(), StartVector, EndVector, FColor::Red);
	//DrawDebugSphere(GetWorld(), EndVector, 10, 10, FColor::Blue, false, 5);

	//Creates a sphere responsable of hit a object in vector trace
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadious);

	return GetWorld()->SweepSingleByChannel(
		HitResult, 
		StartVector, 
		EndVector, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		Sphere
	);

}
