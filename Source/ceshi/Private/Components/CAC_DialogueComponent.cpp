// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CAC_DialogueComponent.h"
#include "GameplayUtil/FuncLib_GameplayUtil.h"

// Sets default values for this component's properties
UCAC_DialogueComponent::UCAC_DialogueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCAC_DialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCAC_DialogueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCAC_DialogueComponent::InitializeDialogueComponent(FName DialogueActorID, UObject* WorldContextObject)
{
	SetDialogueActorID(DialogueActorID);
	UDialogueService* dialogueService = UFuncLib_GameplayUtil::GetDialogueService(WorldContextObject);

	if (dialogueService)
		dialogueService->RegisterDialogueData(GetDialogueActorID(), myDialogueActorData);
}

void UCAC_DialogueComponent::SetDialogueActorID(FName newID)
{
	if (myDialogueActorID == newID)
		return;

	myDialogueActorID = newID;
}

