// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_Core.generated.h"

class UServiceManager;
/**
 * 
 */
UCLASS()
class CESHI_API UGI_Core : public UGameInstance
{
	GENERATED_BODY()

public:
	UGI_Core();

	UFUNCTION()
	void ServicesInitialization();

	UFUNCTION()
	void ServicesBeginPlay();

	UFUNCTION()
	void ServicesShutdown();

	void Init() override;

	void Shutdown() override;

private:
	void OnWorldInitialized(const UWorld::FActorsInitializedParams& param);

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UServiceManager> myServiceManagerClass;

	UPROPERTY()
	UServiceManager* myServiceManagerRef;
};
