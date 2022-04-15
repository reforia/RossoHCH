// Fill out your copyright notice in the Description page of Project Settings.

#include "Services/ServiceManager.h"
#include "Services/ServiceBase.h"
#include "Kismet/GameplayStatics.h"
#include "Services/InventoryService.h"

UServiceManager::UServiceManager()
{
	Services = TArray<UServiceBase*>();
}

UServiceManager::~UServiceManager()
{
}

void UServiceManager::InitializeServices()
{
	for (TSubclassOf<UServiceBase> service : RegisteredServiceList)
	{
		if (!service->IsValidLowLevelFast()) { continue; }

		((UServiceBase*)(service->GetDefaultObject()))->ServiceConstruction(this);
	}

	//for (TSubclassOf<UServiceBase> service : RegisteredServiceList)
	//{
	//	if (!service->IsValidLowLevelFast()) { continue; }

	//	UServiceBase* serviceInst = NewObject<UServiceBase>(this, service->GetFName(), RF_NoFlags, service->GetDefaultObject());
	//	serviceInst->ServiceConstruction();
	//	Services.Add(serviceInst);
	//}
}

UInventoryService* UServiceManager::GetInventoryService()
{
	return GetServiceByClassT<UInventoryService>();
}
