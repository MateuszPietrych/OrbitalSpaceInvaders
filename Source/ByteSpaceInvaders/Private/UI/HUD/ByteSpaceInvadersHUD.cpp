// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ByteSpaceInvadersHUD.h"
#include "UI/Widget/ByteSpaceInvadersUserWidget.h"
#include "Controller/UIController.h"

UUIController* AByteSpaceInvadersHUD::GetUIController(const FUIControllerParams& UICParams)
{
	if (WidgetController == nullptr)
	{
		WidgetController = NewObject<UUIController>(this, OrbWidgetControllerClass);
		WidgetController->SetWidgetControllerParams(UICParams);
		WidgetController->BindCallbacksToDependencies();
	}
	return WidgetController;
}