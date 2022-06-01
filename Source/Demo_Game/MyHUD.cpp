// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Todd.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

void AMyHUD::DrawHUD()
{
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	dims.X = ViewportSize.X;
	dims.Y = ViewportSize.Y;
	DrawWidgets();
	//DrawHealthBar();
	DrawMessages();
}


void AMyHUD::DrawHealthBar()
{	
	//get game play stats for the main character
	ATodd *avatar = Cast<ATodd>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	float barWidth = 200, barHeight = 50, barPad = 12, barMargin = 50;
	float percHp = avatar->hp / avatar->maxHp;

	//get screen size
	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	//the x quad to start health bar
	float xSpot = ViewportSize.X - barWidth - barPad - barMargin;
	//the y quad to start health bar
	float ySpot = ViewportSize.Y - barHeight - barPad - barMargin;
	
	float barWidthWithPad = barWidth + 2 * barPad;
	float barHeightWithPad = barHeight + 2 * barPad;
	//draws rectangle by color at spot x,y on hud with width and height specified
	DrawRect(FLinearColor(0, 0, 0, 1), xSpot, ySpot, barWidthWithPad, barHeightWithPad);

	//draws the remaining health on health bar
	DrawRect(FLinearColor(1 - percHp, percHp, 0, 1), ViewportSize.X
		- barWidth - barMargin, ViewportSize.Y - barHeight - barMargin,
		barWidth*percHp, barHeight);
}

void AMyHUD::DrawWidgets()
{
	for (int count = 0; count < widgets.Num(); count++) 
	{
		DrawTexture(widgets[count].icon.tex,
			widgets[count].pos.X,
			widgets[count].pos.Y,
			widgets[count].size.X,
			widgets[count].size.Y, 0, 0, 1, 1);

		DrawText(widgets[count].icon.name,
			FLinearColor::Yellow,
			widgets[count].pos.X,
			widgets[count].pos.Y,
			HUDFont, .6f, false);
	}
}

void AMyHUD::DrawMessages() 
{
	for (int c = messages.Num() - 1; c >= 0; c--) {

		//background box for message
		float outputWidth, outputHeight, pad = 10.f;
		GetTextSize(messages[c].message, outputWidth, outputHeight, HUDFont, 1.f);
		float messageHeight = outputHeight + 2.f * pad;
		float x = 0.f, y = c * messageHeight;

		//black backing
		DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, messageHeight);

		//draw message
		DrawText(messages[c].message, messages[c].color, x + pad, y + pad, HUDFont);


		//reduce time by time since last  frame
		messages[c].time -= GetWorld()->GetDeltaSeconds();

		//remove message
		if (messages[c].time < 0)
		{
			messages.RemoveAt(c);
		}


	}
}

void AMyHUD::addMessage(Message msg)
{
	messages.Add(msg);
}

void AMyHUD::addWidget(Widget widget) 
{
	//find the pos on the grid for the widget and draw the icon
	FVector2D start(200, 200), pad(12, 12);
	widget.size = FVector2D(100, 100);
	widget.pos = start;
	for (int c = 0; c < widgets.Num(); c++) 
	{
		widget.pos.X += widget.size.X + pad.X;

		// if the dimension of screen is smaller than the widget go to next line
		if (widget.pos.X + widget.size.X > dims.X)
		{
			widget.pos.X = start.X;
			widget.pos.Y = widget.size.Y + pad.Y;
		}
	}
	widgets.Add(widget);
}

void AMyHUD::clearWidgets()
{
	widgets.Empty();
}

void AMyHUD::MouseClicked() {
	FVector2D mouse;
	APlayerController* Pcontroller = GetWorld()->GetFirstPlayerController();
	Pcontroller->GetMousePosition(mouse.X, mouse.Y);
	heldWidget = nullptr;

		for (size_t i = 0; i < widgets.Num(); i++)
		{
			if (widgets[i].hit(mouse))
			{
				heldWidget = &widgets[i];
				return;
			}
		}

}

void AMyHUD::MouseMoved() {
	static FVector2D lastMouse;
	FVector2D thisMouse, dMouse;
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	PController->GetMousePosition(thisMouse.X, thisMouse.Y);
	dMouse - thisMouse - lastMouse;

	float time = PController->GetInputKeyTimeDown(EKeys::LeftMouseButton);

	if (time > 0.f && heldWidget)
	{
		heldWidget->pos.X += dMouse.X;
		heldWidget->pos.Y += dMouse.Y;
	}

	lastMouse = thisMouse;

}
