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
	if (owner)
		owner->myServices.Add(this);
}

void UServiceBase::ServiceBeginPlay()
{

}

void UServiceBase::ServiceShutdown()
{

}
