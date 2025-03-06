// Copyright GleeN


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		//Create instance of Overlay Widget Controller from blueprint
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		//Set its parameters
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		//Bind callback functions to delegates listening for attribute changes
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{	//Check if Overlay widget and overlay widget controller are set in HUD blueprint
	checkf(OverlayWidgetClass, TEXT("Overlay widget class uninitialized fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class uninitialized fill out BP_AuraHUD"));

	//Create instance of Overlay widget
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	//Cast to UAuraUserWidget to use SetWidgetController() function
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	
	//Get Overlay Widget Controller
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	//Widget and Overlay Widget point to the same memory if cast was successful but it's safer to use Widget
	Widget->AddToViewport();
}

