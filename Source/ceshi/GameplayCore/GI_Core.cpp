// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Core.h"
#include "Services/ServiceManager.h"
#include "Misc/CoreDelegates.h"
#include "Engine/World.h"

UGI_Core::UGI_Core()
{
	FWorldDelegates::OnWorldInitializedActors.AddUObject(this, &UGI_Core::OnWorldInitialized);
}

void UGI_Core::ServicesInitialization()
{
	if (ServiceManagerClass)
	{
		ServiceManagerRef = NewObject<UServiceManager>(this, ServiceManagerClass, NAME_None, RF_NoFlags, ServiceManagerClass->GetDefaultObject(), true);
		ServiceManagerRef->InitializeServices();
	}
}

void UGI_Core::ServicesBeginPlay()
{
	if (ServiceManagerRef)
		ServiceManagerRef->TriggerBeginPlayForServices();

}

void UGI_Core::ServicesShutdown()
{
	if (ServiceManagerRef)
		ServiceManagerRef->ShutdownServices();
}

void UGI_Core::Init()
{
	UGameInstance::Init();
	ServicesInitialization();
}

void UGI_Core::Shutdown()
{
	ServicesShutdown();
	UGameInstance::Shutdown();
}

void UGI_Core::OnWorldInitialized(const UWorld::FActorsInitializedParams& param)
{
	if (param.World)
		param.World->OnWorldBeginPlay.AddUObject(this, &UGI_Core::ServicesBeginPlay);
}

