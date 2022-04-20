// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/ServiceBase.h"
#include "QuestService.generated.h"

class UQuestContextObject;
/**
 * 
 */
UCLASS(Blueprintable)
class CESHI_API UQuestService : public UServiceBase
{
	GENERATED_BODY()
	
public:
	void ServiceConstruction(UServiceManager* owner) override;

	void ServiceBeginPlay() override;

	void ServiceShutdown() override;

	FString GetDebugLogInfo() override;

private:
	UFUNCTION()
	void InitializeQuestLines();

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "RegisteredQuestLines"))
	TArray<TSubclassOf<UQuestContextObject>> myRegisteredQuestLines;

private:
	UPROPERTY()
	TArray<UQuestContextObject*> myQuestLinesList;
};
