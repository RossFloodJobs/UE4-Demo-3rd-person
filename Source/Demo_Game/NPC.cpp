// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"
#include "GameFramework/PlayerController.h"
#include "Todd.h"
#include "MyHud.h"


ANPC::ANPC(const FObjectInitializer& ObjectInitializer)
{
	//creating sphere object for a proximity bubble
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this,
		TEXT("Proximity Sphere"));
	ProxSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	ProxSphere->SetSphereRadius(32.0f);
	// Code to make ANPC::Prox() run when this proximity sphere 
	// overlaps another actor. 
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
	NpcMessage = "Yo... Sup.";//default message, can be edited in blueprints
	
}

int ANPC::Prox_Implementation(UPrimitiveComponent*  OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if overlapping actor is not the player return from the function
	if (Cast<ATodd>(OtherActor) == nullptr)
	{
		return -1;
	}

	//get player controller
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	if (PController)
	{
		AMyHUD * hud = Cast<AMyHUD>(PController->GetHUD());
		hud->addMessage(Message(NpcMessage, 5.f, FColor::White));
	}
	return 0;
}
// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

