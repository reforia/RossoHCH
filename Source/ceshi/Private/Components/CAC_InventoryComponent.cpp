// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CAC_InventoryComponent.h"
#include "Services/Inventory/InventoryService.h"
#include "GameplayUtil/FuncLib_GameplayUtil.h"

// Sets default values for this component's properties
UCAC_InventoryComponent::UCAC_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCAC_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCAC_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCAC_InventoryComponent::InitializeInventoryComponent(FName inventoryID, UObject* WorldContextObject)
{
	SetInventoryID(inventoryID);
	UInventoryService* invService = UFuncLib_GameplayUtil::GetInventoryService(WorldContextObject);

	if (invService)
		invService->RegisterInventoryID(inventoryID);
}

void UCAC_InventoryComponent::SetInventoryID(FName newID)
{
	if (myInventoryID == newID)
		return;

	myInventoryID = newID;
}
