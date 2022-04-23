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

	UFUNCTION(BlueprintPure, Category = "ServiceHelper")
	virtual FString GetDebugLogInfo();

	UFUNCTION()
	virtual void ServiceConstruction(UServiceManager* owner);

	UFUNCTION()
	virtual void ServiceBeginPlay();

	UFUNCTION()
	virtual void ServiceShutdown();

	UFUNCTION()
	void SetOwner(UServiceManager* newSM) { if (myServiceManagerOwner == newSM) return; myServiceManagerOwner = newSM; };

	UWorld* GetWorld() const override;

private:
	UPROPERTY()
	UServiceManager* myServiceManagerOwner;
};
