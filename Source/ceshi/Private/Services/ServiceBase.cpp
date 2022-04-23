// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/ServiceBase.h"
#include "Services/ServiceManager.h"

UServiceBase::UServiceBase()
{

}

UServiceBase::~UServiceBase()
{
}

FString UServiceBase::GetDebugLogInfo()
{
	return "";
}

void UServiceBase::ServiceConstruction(UServiceManager* owner)
{
	SetOwner(owner);

	if (owner)
		owner->myServices.Add(this);
}

void UServiceBase::ServiceBeginPlay()
{

}

void UServiceBase::ServiceShutdown()
{

}

UWorld* UServiceBase::GetWorld() const
{
	if(myServiceManagerOwner)
		return myServiceManagerOwner->GetWorld();

	return nullptr;
}
