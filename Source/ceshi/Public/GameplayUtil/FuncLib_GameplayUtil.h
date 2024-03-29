// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FuncLib_GameplayUtil.generated.h"

class UGI_Core;
class UServiceManager;
class UInventoryService;
class UQuestService;
class UCharService;
class APawn;

/**
 * 
 */
UCLASS()
class CESHI_API UFuncLib_GameplayUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UGI_Core* GetGICore(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UServiceManager* GetServiceManager(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UInventoryService* GetInventoryService(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UQuestService* GetQuestService(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UCharService* GetCharService(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UDialogueService* GetDialogueService(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static AActor* GetCharByID(const FName charID, const UObject* WorldContextObject);
};
