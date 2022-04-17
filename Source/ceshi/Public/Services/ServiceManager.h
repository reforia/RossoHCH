// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ServiceManager.generated.h"


class UServiceBase;
class UInventoryService;

/**
 * 
 */
UCLASS(Blueprintable)
class CESHI_API UServiceManager : public UObject
{
	GENERATED_BODY()

public:
	UServiceManager();
	~UServiceManager();

	UFUNCTION(BlueprintCallable, Category = "Service Manager")
	void InitializeServices();
	
	UFUNCTION()
	void TriggerBeginPlayForServices();

	UFUNCTION()
	void ShutdownServices();

	TArray<UServiceBase*> GetServices() { return Services; };

	template<typename T> T* GetServiceByClassT() 
	{
		for (UServiceBase* service : GetServices())
		{
			//if(service->GetClass()->GetFName() == T::StaticClass.GetFName())
			FString a = service->GetClass()->GetName();
			FString b = T::StaticClass()->GetName();

			// THIS IS A GIANTTTT HAAAACCCKKK!!!!!!!!!
			if(a.Contains(b))
				return static_cast<T*>(service);
		}

		return (T*)nullptr;
	}

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Service Manager")
	TArray<TSubclassOf<UServiceBase>> RegisteredServiceList;

public:
	UPROPERTY()
	TArray<UServiceBase*> Services;
};
