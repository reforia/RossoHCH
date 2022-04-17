// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Quest/QuestContextObject.h"

void UQuestContextObject::Tick(float DeltaTime)
{
	if (!ShouldTick)
		return;

	UpdateCurrentQuestLineState();
}

UQuestContextObject::UQuestContextObject()
{
	QuestsInQuestLine = TMap<UQuestObject*, FStruct_QuestData>();
}

UQuestContextObject::~UQuestContextObject()
{
	QuestsInQuestLine.Empty();
}

void UQuestContextObject::UpdateCurrentQuestLineState()
{
	if (GetCurrentQuestLineState() == EQuestLineState::EV_Finished)
		return;

	if (QuestsInQuestLine.Num() <= 0)
		return;

	uint32 lockedQuestCount = 0;
	uint32 finishedQuestCount = 0;
	// Find the current tracking quests (First couple, or in the middle), basically, go through each quest object, and get it's state, then do a switch
	TArray<UQuestObject*> allQuestList;
	GetAllQuestObjects(allQuestList);
	for (UQuestObject* QuestObj : allQuestList)
	{
		const FStruct_QuestData QuestDataRef = QuestsInQuestLine[QuestObj];

		if(!IsValid(QuestObj))
			continue;

		EQuestState tmpState = QuestObj->GetCurrentQuestState();

		switch (tmpState)
		{
		case EQuestState::EV_Locked:
		{
			bool previousQuestAllCompleted = true;

			for (FName questLinkedID : QuestDataRef.PreviousQuestsLinkedIDs)
			{
				UQuestObject* previousQuestObjRef = GetQuestObjectByID(questLinkedID);
				if (previousQuestObjRef)
				{
					if (previousQuestObjRef->GetCurrentQuestState() != EQuestState::EV_Succeeded)
					{
						previousQuestAllCompleted = false;
						break;
					}
				}
			}
			if (previousQuestAllCompleted && QuestObj->GetQuestUnlockPrecondition())
				QuestObj->SetCurrentQuestState(EQuestState::EV_Unlocked);
			break;
		}
		case  EQuestState::EV_Unlocked:
			// Anything that needs the player know that the quest is unlocked
			QuestObj->SetCurrentQuestState(EQuestState::EV_InProgress);
			QuestObj->OnQuestBegin();
			break;
		case EQuestState::EV_InProgress:
			break;
		case EQuestState::EV_Succeeded:
			break;
		case EQuestState::EV_Failed:
			break;
		default:
			break;
		}

		tmpState = QuestObj->GetCurrentQuestState();

		if (tmpState == EQuestState::EV_Failed || tmpState == EQuestState::EV_Succeeded)
		{
			finishedQuestCount++;
			continue;
		}

		if (tmpState == EQuestState::EV_Locked)
			lockedQuestCount++;
	}

	if (lockedQuestCount == QuestsInQuestLine.Num())
		SetCurrentQuestLineState(EQuestLineState::EV_Locked);
	else if (finishedQuestCount == QuestsInQuestLine.Num())
		SetCurrentQuestLineState(EQuestLineState::EV_Finished);
	else
		SetCurrentQuestLineState(EQuestLineState::EV_Unlocked);
}

void UQuestContextObject::InitializeCurrentQuestLine()
{
	// Load Everything in the DB to the Quests List
	if (!QuestLineDatabase)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, "Quest Line DB Not Assigned for Quest Context Object! ABORT EXECUTION");
		return;
	}

	TArray<FStruct_QuestData*> tmpQuestsData;
	QuestLineDatabase->GetAllRows<FStruct_QuestData>("", tmpQuestsData);

	for (FStruct_QuestData* perQuestData : tmpQuestsData)
	{
		if (!perQuestData)
			continue;

		UQuestObject* questObj = NewObject<UQuestObject>(this, perQuestData->QuestObjectClass, NAME_None, RF_NoFlags, perQuestData->QuestObjectClass->GetDefaultObject(), true);
		QuestsInQuestLine.Add(questObj, *perQuestData);
	}
}

void UQuestContextObject::SetCurrentQuestLineState(EQuestLineState newState)
{
	if (newState == GetCurrentQuestLineState())
		return;

	CurrentQuestLineState = newState;
	OnQuestlineStateChanged.Broadcast(CurrentQuestLineState);
}

UQuestObject* UQuestContextObject::GetQuestObjectByID(FName ID)
{
	FStruct_QuestData* tmpQuestData = QuestLineDatabase->FindRow<FStruct_QuestData>(ID, "");
	if (!tmpQuestData)
		return nullptr;


	TArray<UQuestObject*> allQuests;
	GetAllQuestObjects(allQuests);
	for (UQuestObject* questObject : allQuests)
	{
		if (QuestsInQuestLine[questObject] == *tmpQuestData)
			return questObject;
	}

	return nullptr;
}

void UQuestContextObject::GetAllQuestObjects(TArray<UQuestObject*>& outQuestList)
{
	QuestsInQuestLine.GetKeys(outQuestList);
}
