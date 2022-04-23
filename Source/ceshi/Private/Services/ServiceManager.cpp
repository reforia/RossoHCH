// Fill out your copyright notice in the Description page of Project Settings.

#include "Services/ServiceManager.h"
#include "Services/ServiceBase.h"
#include "Kismet/GameplayStatics.h"
#include "Services/Inventory/InventoryService.h"
#include "../GameplayCore/GI_Core.h"

UServiceManager::UServiceManager()
{
	myServices = TArray<UServiceBase*>();
}

UServiceManager::~UServiceManager()
{
}

void UServiceManager::InitializeServices()
{
	for (TSubclassOf<UServiceBase> service : myRegisteredServiceList)
	{
		if (!service->IsValidLowLevelFast()) { continue; }

		((UServiceBase*)(service->GetDefaultObject()))->ServiceConstruction(this);
	}
}

void UServiceManager::TriggerBeginPlayForServices()
{
	for (UServiceBase* service : GetServices())
		service->ServiceBeginPlay();
}

void UServiceManager::ShutdownServices()
{
	for (UServiceBase* service : GetServices())
		service->ServiceShutdown();
}

UWorld* UServiceManager::GetWorld() const
{
	return myCurrentActiveWorld;
}

