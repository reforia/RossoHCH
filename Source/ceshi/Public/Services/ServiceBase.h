// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ServiceBase.generated.h"

class UServiceManager;
/**
 * 
 */
UCLASS(BlueprintType)
class CESHI_API UServiceBase : public UObject
{
	GENERATED_BODY()

public:
	UServiceBase();
	virtual ~UServiceBase();

	virtual void ServiceConstruction(UServiceManager* owner);
};
