#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "MoverComponent.h"
#include "TriggerComponent.h"
#include "TriggerMaster.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONRAIDER_API UTriggerMaster : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerMaster();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	FName NameTagToUnlock;

	UPROPERTY(BlueprintReadWrite)
	TArray<UTriggerComponent*> MyTriggers;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMoverComponent* NewMover);

private:
	UMoverComponent* Mover;

};
