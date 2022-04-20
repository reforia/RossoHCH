// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Quest/QuestObject.h"
#include "DelayAction.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "GameplayUtil/FuncLib_GameplayUtil.h"

void UQuestObject::SetCurrentQuestState(EQuestState newState)
{
	if (newState == GetCurrentQuestState())
		return;

	myCurrentQuestState = newState;
	// OnQuestStateChanged.Broadcast(myCurrentQuestState);
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

	if (GWorld)
		return GWorld;

	return nullptr;
}


void UQuestObject::QuestDelay(float Duration, struct FLatentActionInfo LatentInfo)
{
	if (UWorld* World = this->GetWorld())
	{
		UKismetSystemLibrary::Delay(this, Duration, LatentInfo);
	}
}

APawn* UQuestObject::QuestGetPawnByID(FName charID)
{
	if (UWorld* World = this->GetWorld())
	{
		AActor* actor = UFuncLib_GameplayUtil::GetCharByID(charID, this);
		APawn* pawn = Cast<APawn>(actor);
		if (!pawn)
			return nullptr;

		return pawn;
	}
	return nullptr;
}
