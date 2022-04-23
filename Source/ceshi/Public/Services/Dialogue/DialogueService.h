// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/ServiceBase.h"
#include "Engine/DataTable.h"
#include "DialogueService.generated.h"

class UDialogue;

USTRUCT(BlueprintType)
struct FStruct_DialogueActorData
{
	GENERATED_USTRUCT_BODY()

public:
	FStruct_DialogueActorData()
		:myDefaultDialogueID(""), myOverrideDialogueID("")
	{}

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Char", meta = (DisplayName = "DefaultDialogueID"))
		FName myDefaultDialogueID;

	UPROPERTY(BlueprintReadOnly, Category = "Char", meta = (DisplayName = "OverrideDialogueID"))
		FName myOverrideDialogueID;
};

USTRUCT(BlueprintType)
struct FStruct_DialogueData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FStruct_DialogueData()
		:myDialogueID(""), myDialogue(nullptr)
	{}

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Char", meta = (DisplayName = "DialogueID"))
	FName myDialogueID;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Char", meta = (DisplayName = "Dialogue"))
	UDialogue* myDialogue;
};

/**
 * 
 */
UCLASS(Blueprintable)
class CESHI_API UDialogueService : public UServiceBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void RegisterDialogueData(FName dialogueActorID, FStruct_DialogueActorData dialogueActorData);

	UFUNCTION()
	bool DoesDialoguesContainData(FName dialogueActorID);

	UFUNCTION()
	TArray<FName> GetAllDialogueActorIDs();

	UFUNCTION(BlueprintPure, Category = "Dialogue")
	UDialogue* GetDefaultDialogueByDialogueActorID(FName dialogueActorID);

	UFUNCTION(BlueprintPure, Category = "Dialogue")
	UDialogue* GetOverrideDialogueByDialogueActorID(FName dialogueActorID);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Dialogue")
	void PlayDialogueForDialogueActorID(FName dialogueActorID, FName leftCharID, FName rightCharID);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetOverrideDialogueToDialogueActor(FName dialogueActorID, FName overrideDialogueID);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void ClearOverrideDialogueToDialogueActor(FName dialogueActorID);

	UFUNCTION()
	UDialogue* GetDialogueByDialogueID(FName dialogueID);

	FStruct_DialogueActorData* GetDialogueActorDataByID(const FName dialogueActorID);

	void ServiceConstruction(UServiceManager* owner) override;

	FString GetDebugLogInfo() override;

	void ServiceShutdown() override;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Dialogue", meta = (DisplayName = "DialogueDatabase"))
	class UDataTable* myDialogueDatabase;

private:
	UPROPERTY()
	TMap<FName, FStruct_DialogueActorData> myDialogues;
};
