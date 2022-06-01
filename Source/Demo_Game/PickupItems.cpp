// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupItems.h"
#include "Todd.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "MyHUD.h"


// Sets default values
APickupItems::APickupItems(const FObjectInitializer& ObjectInitializer)
{
	Name = "DEFAULT_ITEM";
	Quantity = 0;

	//initialize objects
	ProxSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));

	RootComponent = Mesh;

	//this lets dropped or moved item move around enviroment
	Mesh->SetSimulatePhysics(true);

	//run APickupItems::Prox when this objects ProxSphere overlaps another actor
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItems::Prox);

	//attach mesh to proxsphere so that the proxsphere moves with the mesh when object is moved
	ProxSphere->AttachToComponent(Mesh, FAttachmentTransformRules::KeepWorldTransform);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

int APickupItems::Prox_Implementation(UPrimitiveComponent* OverlappedComponent,
										AActor* OtherActor,
										UPrimitiveComponent* OtherComponent,
										int32 OtherBodyIndex,
										bool bFromSweep,
										const FHitResult& SweepResult)
{
	//if actor entire shpere not player then return
	if (Cast<ATodd>(OtherActor) == nullptr)
	{
		return -1;
	}

	//get reference to player avatar to give item
	ATodd* todd = Cast<ATodd>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	//player pickupitem
	todd->Pickup(this);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Todd has item?");

	//send message to hud
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	FString inputMessage = FString("Picked up: ") + FString::FromInt(Quantity) + FString(" ") + Name;
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->addMessage(Message(Icon, inputMessage, 5.f, FColor::White));

	Destroy();
	return 0;
}

// Called when the game starts or when spawned
void APickupItems::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

