// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PickupItems.generated.h"

UCLASS()
class DEMO_GAME_API APickupItems : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItems(const FObjectInitializer& ObjectInitializer);

	//Item Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		FString Name;

	//Number of items in inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		int32 Quantity;

	//collision sphere to pick up item
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
		USphereComponent* ProxSphere;

	//items static mesh
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
		UStaticMeshComponent* Mesh;

	//items inventory icon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
		UTexture2D* Icon;
	
	//when an actor comes inside Proxshpere run this function
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
		void Prox(UPrimitiveComponent* OverlappedComponent,
					AActor* OtherActor,
					UPrimitiveComponent* OtherComponent,
					int32 OtherBodyIndex,
					bool bFromSweep,
					const FHitResult& SweepResult);

	virtual int Prox_Implementation(UPrimitiveComponent* OverlappedComponent,
					AActor* OtherActor,
					UPrimitiveComponent* OtherComponent,
					int32 OtherBodyIndex,
					bool bFromSweep,
					const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
