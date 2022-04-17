// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayUtil/FuncLib_GameplayUtil.h"
#include "Services/ServiceManager.h"
#include "Services/Inventory/InventoryService.h"
#include "Services/Quest/QuestService.h"
#include "../GameplayCore/GI_Core.h"
#include "Kismet/GameplayStatics.h"

UGI_Core* UFuncLib_GameplayUtil::GetGICore(const UObject* WorldContextObject)
{
	UGI_Core* GIRef = Cast<UGI_Core>(UGameplayStatics::GetGameInstance(UGameplayStatics::GetGameInstance(WorldContextObject->GetWorld())));
	return GIRef;
}

UServiceManager* UFuncLib_GameplayUtil::GetServiceManager(const UObject* WorldContextObject)
{
	UGI_Core* GIRef = GetGICore(WorldContextObject);
	if (!GIRef)
		return nullptr;

	return GIRef->ServiceManagerRef;
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
