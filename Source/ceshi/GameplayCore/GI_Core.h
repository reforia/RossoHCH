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
	UFUNCTION()
	void ServicesInitialization();

	void Init() override;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UServiceManager> ServiceManagerClass;

	UPROPERTY()
	UServiceManager* ServiceManagerRef;
};
