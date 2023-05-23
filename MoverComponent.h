#pragma once

#include "Math/UnrealMathUtility.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONRAIDER_API UMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetShouldMove(bool ToMove);

	UFUNCTION(BlueprintCallable)
	bool GetShouldMove();

private:
	UPROPERTY(EditAnywhere)
	FVector SetOffVector;

	UPROPERTY(EditAnywhere)
	float TimeToMove;

	bool ShouldMove = false;

	FVector OriginalLocation;

};
