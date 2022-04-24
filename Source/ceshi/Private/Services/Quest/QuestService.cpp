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

	if (myQuestLinesList.Num() <= 0)
	{
		result += "ERROR GETTING QUEST LINES LIST!!";
		return result;
	}


	for (UQuestContextObject* questContextObj : myQuestLinesList)
	{
		if(!IsValid(questContextObj))
			continue;

		result = result + "QuestLine DB: " + questContextObj->myQuestLineDatabase->GetName() + "\n";
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

void UQuestService::TryCompleteQuest(UDataTable* dataTable, FName questID, bool success)
{
	for (UQuestContextObject* questLines : myQuestLinesList)
	{
		if (questLines->myQuestLineDatabase == dataTable)
		{
			questLines->RequestCompleteQuestByID(questID, success);
			return;
		}
	}
}

void UQuestService::ServiceShutdown()
{
	for (UQuestContextObject* questLine : myQuestLinesList)
		questLine->myShouldTick = false;

	myQuestLinesList.Empty();
}

void UQuestService::ServiceBeginPlay()
{
	for (UQuestContextObject* questLine : myQuestLinesList)
		questLine->myShouldTick = true;
}

void UQuestService::InitializeQuestLines()
{
	for (TSubclassOf<UQuestContextObject> questLineClass : myRegisteredQuestLines)
	{
		UQuestContextObject* newQuestLineObj = NewObject<UQuestContextObject>(this, questLineClass, NAME_None, RF_NoFlags, questLineClass->GetDefaultObject(), true);
		if (newQuestLineObj)
		{
			newQuestLineObj->InitializeCurrentQuestLine(); // Create Quest Objects and load them into Quest Context Object
			myQuestLinesList.Add(newQuestLineObj);
		}
	}
}

TArray<FStruct_QuestData> UQuestService::GetAllQuests()
{
	TArray<FStruct_QuestData> allQuests;

	for (UQuestContextObject* questContextObj : myQuestLinesList)
	{
		if (!IsValid(questContextObj))
			continue;

		TArray<FStruct_QuestData> tmpQuestsData;
		questContextObj->GetAllQuestsData(tmpQuestsData);
		allQuests.Append(tmpQuestsData);
	}
	return allQuests;
}

TArray<FStruct_QuestData> UQuestService::GetAllActiveQuests()
{
	TArray<FStruct_QuestData> allQuests;

	for (UQuestContextObject* questContextObj : myQuestLinesList)
	{
		if (!IsValid(questContextObj))
			continue;

		TArray<FStruct_QuestData> tmpQuestsData;
		questContextObj->GetAllActiveQuestsData(tmpQuestsData);
		allQuests.Append(tmpQuestsData);
	}
	return allQuests;
}
