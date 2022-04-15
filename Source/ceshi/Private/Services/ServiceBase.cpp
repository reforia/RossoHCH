// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/ServiceBase.h"
#include "Services/ServiceManager.h"

UServiceBase::UServiceBase()
{

}

UServiceBase::~UServiceBase()
{
}

void UServiceBase::ServiceConstruction(UServiceManager* owner)
{
	if (owner)
		owner->Services.Add(this);
}

