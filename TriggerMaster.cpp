#include "TriggerMaster.h"
#include "MoverComponent.h"

UTriggerMaster::UTriggerMaster()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerMaster::BeginPlay()
{
    Super::BeginPlay();
}

void UTriggerMaster::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    for(int32 index = 0; index < MyTriggers.Max(); ++index)
    {
        if(MyTriggers[index]->GetToUnlock() != false)
        {
            UE_LOG(LogTemp, Display, TEXT("TRUE"));
            Mover->SetShouldMove(true);
        }else
        {
            UE_LOG(LogTemp, Display, TEXT("FALSE"));
            Mover->SetShouldMove(false);
        }
    }    

}

void UTriggerMaster::SetMover(UMoverComponent* NewMover)
{
	Mover = NewMover;
}
