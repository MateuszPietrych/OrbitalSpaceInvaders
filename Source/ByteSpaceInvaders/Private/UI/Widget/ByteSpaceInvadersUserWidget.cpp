// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/ByteSpaceInvadersUserWidget.h"
#include "Controller/UIController.h"



void UByteSpaceInvadersUserWidget::SetUIController(UUIController* NewUIController)
{
	UIController = NewUIController;
	UIControllerSet();
}
