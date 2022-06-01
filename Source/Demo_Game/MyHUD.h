// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

struct Message
{
	FString message;
	float time;
	FColor color;
	UTexture2D* texture;

	Message()
	{
		time = 5.f;
		color = FColor::White;
	}
	Message(FString iMessage, float iTime, FColor iColor)
	{
		message = iMessage;
		time = iTime;
		color = iColor;
	}

	Message(UTexture2D* iImage, FString iMessage, float iTime, FColor iColor)
	{

		texture = iImage;
		message = iMessage;
		time = iTime;
		color = iColor;

	}

};

struct Icon
{
	FString name;
	UTexture2D* tex;
	
	Icon() {
		name = "UNKNOWN ICON";
		tex = 0;
	}

	Icon(FString& iName, UTexture2D* iTex)
	{
		name = iName;
		tex = iTex;
	}
};

struct Widget
{
	Icon icon;
	FVector2D pos, size;

	Widget(Icon iIcon) 
	{
		icon = iIcon;
	}

	float left() { return pos.X; }
	float right() { return pos.X + size.X;}
	float top() { return pos.Y;}
	float bottom() { return pos.Y + size.Y;}

	bool hit(FVector2D p) {
		return p.X > left() && p.X < right() && p.Y > top() && p.X < bottom();
	}

};

/**
 * 
 */
UCLASS()
class DEMO_GAME_API AMyHUD : public AHUD
{
	GENERATED_BODY()


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
		UFont* HUDFont;
	TArray<Message> messages;

	//array of widgets to display inventory
	TArray<Widget> widgets;
	Widget* heldWidget;

	//the screens dimensions
	FVector2D dims;

	//draws
	virtual void DrawHUD() override;
	void DrawWidgets();
	void DrawMessages();
	void DrawHealthBar();

	//clears
	void clearWidgets();

	//adds
	void addWidget(Widget widget);
	void addMessage(Message msg);
	

	//mouse
	void MouseClicked();
	void MouseMoved();
	
};
