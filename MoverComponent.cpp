#include "MoverComponent.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	//Sets The ORIGINAL location of the actor
	OriginalLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Set current location of actor, destination actor and a float is assigned a m/s calculation 
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector DestinationVector = OriginalLocation + SetOffVector;
	float Speed = (FVector::Distance(OriginalLocation, DestinationVector) / TimeToMove);
	
	if(ShouldMove){
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, DestinationVector, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);
	}else{
		FVector ReturnLocation = FMath::VInterpConstantTo(CurrentLocation, OriginalLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(ReturnLocation);
	}
}

void UMoverComponent::SetShouldMove(bool ToMove)
{
	ShouldMove = ToMove;
}

bool UMoverComponent::GetShouldMove()
{
	return ShouldMove;
}
