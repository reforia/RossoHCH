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
	if (myServiceManagerClass)
	{
		myServiceManagerRef = NewObject<UServiceManager>(this, myServiceManagerClass, NAME_None, RF_NoFlags, myServiceManagerClass->GetDefaultObject(), true);
		myServiceManagerRef->InitializeServices();
	}
}

void UGI_Core::ServicesBeginPlay()
{
	if (myServiceManagerRef)
		myServiceManagerRef->TriggerBeginPlayForServices();

}

void UGI_Core::ServicesShutdown()
{
	if (myServiceManagerRef)
		myServiceManagerRef->ShutdownServices();
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
	{
		if (myServiceManagerRef)
			myServiceManagerRef->SetCurrentActiveWorld(param.World);
		param.World->OnWorldBeginPlay.AddUObject(this, &UGI_Core::ServicesBeginPlay);
	}
}

