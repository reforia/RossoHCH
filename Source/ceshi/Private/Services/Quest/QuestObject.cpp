// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Quest/QuestObject.h"
#include "DelayAction.h"

void UQuestObject::SetCurrentQuestState(EQuestState newState)
{
	if (newState == GetCurrentQuestState())
		return;

	CurrentQuestState = newState;
	// OnQuestStateChanged.Broadcast(CurrentQuestState);
}

bool UQuestObject::GetQuestUnlockPrecondition_Implementation()
{
	return true;
}

void UQuestObject::CompleteQuest(bool Succeeded)
{
	EQuestState currentState = GetCurrentQuestState();
	if (currentState != EQuestState::EV_InProgress)
		return;

	SetCurrentQuestState(Succeeded ? EQuestState::EV_Succeeded : EQuestState::EV_Failed);
}

class UWorld* UQuestObject::GetWorld() const
{
	Super::GetWorld();
	UObject* Outer = GetOuter();

	while (Outer)
	{
		UWorld* World = Outer->GetWorld();
		if (World)
		{
			return World;
		}

		Outer = Outer->GetOuter();
	}

	return nullptr;
}


void UQuestObject::QuestDelay(UObject* WorldContextObject, float Duration /*= 2.f*/)
{
	if (UWorld* World = this->GetWorld())
	{
		FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = WorldContextObject;
		LatentInfo.ExecutionFunction = TEXT("OnDelayFinished");
		LatentInfo.Linkage = 0;
		LatentInfo.UUID = FMath::Rand();
		LatentActionManager.AddNewAction(WorldContextObject, LatentInfo.UUID, new FDelayAction(Duration, LatentInfo));

	}

}

void UQuestObject::OnDelayFinished()
{

}
