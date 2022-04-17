// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Quest/QuestService.h"
#include "Services/Quest/QuestContextObject.h"

void UQuestService::ServiceConstruction(UServiceManager* owner)
{
	// Load All Quest Lines Data
	InitializeQuestLines();

	UServiceBase::ServiceConstruction(owner);
}

FString UQuestService::GetDebugLogInfo()
{
	FString result = "----Quests Debug Info----\n";

	if (QuestLinesList.Num() <= 0)
	{
		result += "ERROR GETTING QUEST LINES LIST!!";
		return result;
	}


	for (UQuestContextObject* questContextObj : QuestLinesList)
	{
		if(!IsValid(questContextObj))
			continue;

		result = result + "QuestLine DB: " + questContextObj->QuestLineDatabase->GetName() + "\n";
		result = result + "QL Status: " + UEnum::GetValueAsString(questContextObj->GetCurrentQuestLineState()) + "\n";

		TArray<UQuestObject*> allQuests;
		questContextObj->GetAllQuestObjects(allQuests);
		for (UQuestObject* perQuestObj : allQuests)
		{
			if (!IsValid(perQuestObj))
				continue;

			result = result + perQuestObj->GetName() + "\n";
			result = result + UEnum::GetValueAsString(perQuestObj->GetCurrentQuestState()) + "\n";
			result += "\n";
		}
	}

	return result;
}

void UQuestService::ServiceShutdown()
{
	for (UQuestContextObject* questLine : QuestLinesList)
		questLine->ShouldTick = false;

	QuestLinesList.Empty();
}

void UQuestService::ServiceBeginPlay()
{
	for (UQuestContextObject* questLine : QuestLinesList)
		questLine->ShouldTick = true;
}

void UQuestService::InitializeQuestLines()
{
	for (TSubclassOf<UQuestContextObject> questLineClass : RegisteredQuestLines)
	{
		UQuestContextObject* newQuestLineObj = NewObject<UQuestContextObject>(this, questLineClass, NAME_None, RF_NoFlags, questLineClass->GetDefaultObject(), true);
		if (newQuestLineObj)
		{
			newQuestLineObj->InitializeCurrentQuestLine(); // Create Quest Objects and load them into Quest Context Object
			QuestLinesList.Add(newQuestLineObj);
		}
	}
}
