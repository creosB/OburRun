#include "ActorMovement.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"

UActorMovement::UActorMovement()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UActorMovement::BeginPlay()
{
	Super::BeginPlay();
	
	//movement
	TransporterInitial = GetOwner()->GetActorLocation().X;
	TransporterCurrent = TransporterInitial;
	TransporterTarget = TransporterInitial + TransporterTarget;
	Forward =  GetOwner()->GetActorLocation();
}

// Called every frame
void UActorMovement::TickComponent(float DeltaTime, ELevelTick TickType,
                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ForwardTransporter(DeltaTime);
}


void UActorMovement::ForwardTransporter(float DeltaTime)
{
	// Calculating movement speed with direction.
	TransporterCurrent = FMath::FInterpConstantTo(TransporterCurrent, TransporterTarget,
	                                              DeltaTime,
	                                              TransporterForwardSpeed);
	Forward.X = TransporterCurrent;
	TransporterTarget += TransporterTarget * 2;
	GetOwner()->SetActorLocation(Forward);
}
