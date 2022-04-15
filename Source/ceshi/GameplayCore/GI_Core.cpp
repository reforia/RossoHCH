// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Core.h"
#include "Services/ServiceManager.h"

void UGI_Core::ServicesInitialization()
{
	if (ServiceManagerClass)
	{
		ServiceManagerRef = NewObject<UServiceManager>(this, ServiceManagerClass, NAME_None, RF_NoFlags, ServiceManagerClass->GetDefaultObject(), true);
		ServiceManagerRef->InitializeServices();
	}

}

void UGI_Core::Init()
{
	Super::Init();
	ServicesInitialization();
}
