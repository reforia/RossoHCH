// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Dialogue/DialogueService.h"
#include "Dialogue.h"

void UDialogueService::RegisterDialogueData(FName dialogueActorID, FStruct_DialogueActorData dialogueActorData)
{
	if (DoesDialoguesContainData(dialogueActorID))
		return;

	myDialogues.Add(dialogueActorID, dialogueActorData);
}

bool UDialogueService::DoesDialoguesContainData(FName dialogueActorID)
{
	TArray<FName> allDialogueActorIDs = GetAllDialogueActorIDs();
	return allDialogueActorIDs.Contains(dialogueActorID);
}

TArray<FName> UDialogueService::GetAllDialogueActorIDs()
{
	TArray<FName> allDialogueActorIDs;
	myDialogues.GetKeys(allDialogueActorIDs);
	return allDialogueActorIDs;
}

UDialogue* UDialogueService::GetDefaultDialogueByDialogueActorID(FName dialogueActorID)
{
	if (!DoesDialoguesContainData(dialogueActorID))
		return nullptr;

	FStruct_DialogueActorData* dialogueActorData = GetDialogueActorDataByID(dialogueActorID);
	if (!dialogueActorData)
		return nullptr;

	return GetDialogueByDialogueID(dialogueActorData->myDefaultDialogueID);
}

UDialogue* UDialogueService::GetOverrideDialogueByDialogueActorID(FName dialogueActorID)
{
	if (!DoesDialoguesContainData(dialogueActorID))
		return nullptr;
	
	FStruct_DialogueActorData* dialogueActorData = GetDialogueActorDataByID(dialogueActorID);
	if (!dialogueActorData)
		return nullptr;

	return GetDialogueByDialogueID(dialogueActorData->myOverrideDialogueID);
}

void UDialogueService::SetOverrideDialogueToDialogueActor(FName dialogueActorID, FName overrideDialogueID)
{
	FStruct_DialogueActorData* dialogueActorData = GetDialogueActorDataByID(dialogueActorID);
	if (!dialogueActorData)
		return;

	dialogueActorData->myOverrideDialogueID = overrideDialogueID;
}

void UDialogueService::ClearOverrideDialogueToDialogueActor(FName dialogueActorID)
{
	FStruct_DialogueActorData* dialogueActorData = GetDialogueActorDataByID(dialogueActorID);
	if (!dialogueActorData)
		return;

	dialogueActorData->myOverrideDialogueID = "";
}

UDialogue* UDialogueService::GetDialogueByDialogueID(FName dialogueID)
{
	FStruct_DialogueData* dialogueData = myDialogueDatabase->FindRow<FStruct_DialogueData>(dialogueID, "");
	if(dialogueData)
		return dialogueData->myDialogue;
	return nullptr;
}

FStruct_DialogueActorData* UDialogueService::GetDialogueActorDataByID(const FName dialogueActorID)
{
	if (!DoesDialoguesContainData(dialogueActorID))
		return nullptr;

	for (FName perDialogueActorID : GetAllDialogueActorIDs())
	{
		if (perDialogueActorID == dialogueActorID)
			return &myDialogues[perDialogueActorID];
	}

	return nullptr;
}

void UDialogueService::ServiceConstruction(UServiceManager* owner)
{
	UServiceBase::ServiceConstruction(owner);
}

FString UDialogueService::GetDebugLogInfo()
{
	FString result;
	result = "----Dialogue Service----\n";
	result = result + "Current available DialogActors: ";
	result.AppendInt(myDialogues.Num());
	result += "\n";
	for (FName actorID : GetAllDialogueActorIDs())
	{
		FStruct_DialogueActorData& dialogueActorData = myDialogues[actorID];
		result = result + "Name: " + actorID.ToString() + " DefaultDlgID: " + dialogueActorData.myDefaultDialogueID.ToString() + ", OverrideDlgID: " + dialogueActorData.myOverrideDialogueID.ToString() + "\n";
	}
	return result;
}

void UDialogueService::ServiceShutdown()
{
	myDialogues.Reset();
}
