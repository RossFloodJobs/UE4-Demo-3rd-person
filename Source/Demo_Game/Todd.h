// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Demo_Game\PickupItems.h>
#include "Todd.generated.h"


class APickupItems;

UCLASS()
class DEMO_GAME_API ATodd : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ATodd();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	TMap<FString, int> pockets;
	TMap<FString, UTexture2D*> Icons;

	bool inventoryShowing;

	void Pickup(APickupItems* item);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input controls
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float amount);
	void MoveRight(float amount);
	void Yaw(float amount);
	void Pitch(float amount);
	void ToggleInventory();
	void mouseClicked();

	float hp;
	float maxHp;

};
