#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorMovement.generated.h"


UCLASS()
class KODOBUR_API UActorMovement : public UActorComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UActorMovement();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	void ForwardTransporter(float DeltaTime);
	
	UPROPERTY(EditAnywhere)
	float TransporterForwardSpeed = 200.0f;

private:
	FVector Forward;
	float TransporterInitial;
	float TransporterCurrent;
	UPROPERTY(EditAnywhere)
	float TransporterTarget = 3000;

	virtual void BeginPlay() override;
};
