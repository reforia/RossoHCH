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
}

UServiceBase* UServiceManager::GetServiceByClass(TSubclassOf<UServiceBase> testAgainstClass)
{
	for (UServiceBase* service : Services)
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
