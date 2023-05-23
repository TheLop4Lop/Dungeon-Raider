#include "TriggerComponent.h"
#include "MoverComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(GetAcceptableActor() != nullptr)
	{
		ToUnlock = true;
		UE_LOG(LogTemp, Display, TEXT("Unlocking"));
	}
	
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for(AActor* Actor: Actors)
	{
		if(Actor->ActorHasTag(NameTagToUnlock))
		{
			UE_LOG(LogTemp, Display, TEXT("Overlapping with TAG"));
			return Actor;
		}
	}
	return nullptr;

}

bool UTriggerComponent::GetToUnlock()
{
	return ToUnlock;
}

void UTriggerComponent::SetToUnlock(bool Lock)
{
	ToUnlock = Lock;
}
