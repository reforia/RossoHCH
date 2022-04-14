// Fill out your copyright notice in the Description page of Project Settings.

#include "Services/ServiceManager.h"
#include "Services/ServiceBase.h"
#include "Kismet/GameplayStatics.h"
#include "Services/InventoryService.h"

UServiceManager::UServiceManager()
{
	Services = new TArray<UServiceBase*>();
}

UServiceManager::~UServiceManager()
{
	delete Services;
	Services = nullptr;
}

void UServiceManager::InitializeServices()
{
	for (TSubclassOf<UServiceBase> service : RegisteredServiceList)
	{
		if (!service->IsValidLowLevelFast()) { continue; }

		auto newServiceObject = NewObject<UServiceBase>(this, service->GetFName(), RF_NoFlags, service->GetDefaultObject());
		Services->Add(newServiceObject);
	}
}

UServiceBase* UServiceManager::GetServiceByClass(TSubclassOf<UServiceBase> testAgainstClass)
{
	for (UServiceBase* service : *Services)
	{
		auto nameA = service->GetName();
		auto nameB = testAgainstClass->GetName();
		if (nameB == nameA)
			return service;
	}
	return nullptr;
}

UInventoryService* UServiceManager::GetInventoryService()
{
	return GetServiceByClassT<UInventoryService>();
}
