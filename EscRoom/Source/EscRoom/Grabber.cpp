// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	FString ObjectName = GetOwner()->GetName();
	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);

	//Getter for components
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("% missing Physics handle component!"), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*Reach;//FVector(0.f, 0.f, 50.f);

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	///Debug code for finding the Object's location and rotation
	/*UE_LOG(LogTemp, Warning, TEXT("Location: %s Rotation %s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString());*/

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
		);

	//Setup query parameters for collisions, so here ignore self.
	FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

	///For ray-tracing query collision
	FHitResult Hit;	
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is hit!"), *(ActorHit->GetName()));
	}
}