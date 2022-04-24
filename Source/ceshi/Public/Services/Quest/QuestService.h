// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/ServiceBase.h"
#include "Services/Quest/QuestObject.h"
#include "QuestService.generated.h"

class UQuestContextObject;
class UQuestObject;

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

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void TryCompleteQuest(UDataTable* dataTable, FName questID, bool success = true);

private:
	UFUNCTION()
	void InitializeQuestLines();

	UFUNCTION(BlueprintPure, Category = "Quest")
	TArray<FStruct_QuestData> GetAllQuests();

	UFUNCTION(BlueprintPure, Category = "Quest")
	TArray<FStruct_QuestData> GetAllActiveQuests();

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "RegisteredQuestLines"))
	TArray<TSubclassOf<UQuestContextObject>> myRegisteredQuestLines;

private:
	UPROPERTY()
	TArray<UQuestContextObject*> myQuestLinesList;
};
