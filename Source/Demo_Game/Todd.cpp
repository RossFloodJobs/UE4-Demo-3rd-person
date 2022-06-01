// Fill out your copyright notice in the Description page of Project Settings.

#include "Todd.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Engine/World.h"
#include "MyHUD.h"
#include "Engine/Engine.h"
#include "PickupItems.h"

// Sets default values
ATodd::ATodd()
{
	hp = 100;
	maxHp = 100;
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATodd::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATodd::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATodd::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	//Action keys input
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ATodd::ToggleInventory);
	
	
	//Movement Axis input
	PlayerInputComponent->BindAxis("Forward", this, &ATodd::MoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &ATodd::MoveRight);

	//mouse inputs
	PlayerInputComponent->BindAxis("Yaw", this, &ATodd::Yaw);
	PlayerInputComponent->BindAxis("Pitch", this, &ATodd::Pitch);
	PlayerInputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &ATodd::mouseClicked);
}

void ATodd::MoveForward(float amount) 
{
	if (inventoryShowing) {
		return;
	}
	if (Controller && amount)
	{
		FVector fwd = GetActorForwardVector();
		AddMovementInput(fwd, amount);
	}
}

void ATodd::MoveRight(float amount)
{
	if (inventoryShowing) {
		return;
	}
	if (Controller&&amount)
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, amount);
	}
}

void ATodd::Yaw(float amount)
{
	if (inventoryShowing) {
		//when inventory shows input is passed to the HUD
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->MouseMoved();
		return;
	}
	else
	{
		AddControllerYawInput(200.f * amount * GetWorld()->GetDeltaSeconds());
	}
	
}

void ATodd::Pitch(float amount)
{
	if (inventoryShowing) {
		//when inventory shows input is passed to the HUD
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->MouseMoved();
		return;
	}
	else
	{
		AddControllerPitchInput(200.f * amount * GetWorld()->GetDeltaSeconds());
	}
}

void ATodd::ToggleInventory()
{

	//get player controller for HUD
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());

	// if inventory up take it down 
	if (inventoryShowing)
	{
		hud->clearWidgets();
		inventoryShowing = false;
		PController->bShowMouseCursor = false;
		return;
	}

	// show inventory
	inventoryShowing = true;
	PController->bShowMouseCursor = false;
	//Iterate through the items in pockets
	for (TMap<FString, int>::TIterator it = pockets.CreateIterator(); it; ++it)
	{
		FString quantityItem = FString::Printf(TEXT("x %d"), it->Value);
		FString nameItem = it->Key;
		//Combine name of item and quantity 
		FString nameAndQuantityOfItem = nameItem + quantityItem;
		UTexture2D* tex;

		if (Icons.Find(nameItem))
		{
			tex = Icons[it->Key];
			hud->addWidget(Widget(Icon(nameAndQuantityOfItem, tex)));
		}
			
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,"Inventory open.");
	}



}

void ATodd::Pickup(APickupItems* item)
{
	//if item in pack increase amount
	if (pockets.Find(item->Name))
	{
		pockets[item->Name] += item->Quantity;
	}
	//if not add item to pack and set amount 
	else
	{
		pockets.Add(item->Name, item->Quantity);
	}
	Icons.Add(item->Name, item->Icon);
}

void ATodd::mouseClicked()
{
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
	hud->MouseClicked();
}