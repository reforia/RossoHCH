// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayUtil/FuncLib_GameplayUtil.h"
#include "Services/ServiceManager.h"
#include "Services/Inventory/InventoryService.h"
#include "Services/Quest/QuestService.h"
#include "Services/Char/CharService.h"
#include "Services/Dialogue/DialogueService.h"
#include "../GameplayCore/GI_Core.h"
#include "Kismet/GameplayStatics.h"

UGI_Core* UFuncLib_GameplayUtil::GetGICore(const UObject* WorldContextObject)
{
	UGI_Core* GIRef = Cast<UGI_Core>(UGameplayStatics::GetGameInstance((WorldContextObject->GetWorld())));
	return GIRef;
}

UServiceManager* UFuncLib_GameplayUtil::GetServiceManager(const UObject* WorldContextObject)
{
	UGI_Core* GIRef = GetGICore(WorldContextObject);
	if (!GIRef)
		return nullptr;

	return GIRef->myServiceManagerRef;
}

UInventoryService* UFuncLib_GameplayUtil::GetInventoryService(const UObject* WorldContextObject)
{
	UServiceManager* SMRef = GetServiceManager(WorldContextObject);
	if (!SMRef)
		return nullptr;

	return SMRef->GetServiceByClassT<UInventoryService>();
}

UQuestService* UFuncLib_GameplayUtil::GetQuestService(const UObject* WorldContextObject)
{
	UServiceManager* SMRef = GetServiceManager(WorldContextObject);
	if (!SMRef)
		return nullptr;

	return SMRef->GetServiceByClassT<UQuestService>();
}

UCharService* UFuncLib_GameplayUtil::GetCharService(const UObject* WorldContextObject)
{
	UServiceManager* SMRef = GetServiceManager(WorldContextObject);
	if (!SMRef)
		return nullptr;

	return SMRef->GetServiceByClassT<UCharService>();
}

UDialogueService* UFuncLib_GameplayUtil::GetDialogueService(const UObject* WorldContextObject)
{
	UServiceManager* SMRef = GetServiceManager(WorldContextObject);
	if (!SMRef)
		return nullptr;

	return SMRef->GetServiceByClassT<UDialogueService>();
}

AActor* UFuncLib_GameplayUtil::GetCharByID(const FName charID, const UObject* WorldContextObject)
{
	UCharService* charService = GetCharService(WorldContextObject);
	if (!charService)
		return nullptr;

	return charService->GetCharActorInWorldByID(charID, WorldContextObject);
}
