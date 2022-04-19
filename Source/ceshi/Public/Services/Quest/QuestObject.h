// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Services/Quest/QuestType.h"
#include "Tickable.h"
#include "GameplayTaskOwnerInterface.h"
#include "QuestObject.generated.h"

USTRUCT(BlueprintType)
struct FStruct_QuestData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FStruct_QuestData()
		: QuestObjectClass(TSubclassOf<UQuestObject>()), PreviousQuestsLinkedIDs(TArray<FName>())
	{}

	bool operator==(const FStruct_QuestData& other) const
	{
		return QuestObjectClass == other.QuestObjectClass
			&& PreviousQuestsLinkedIDs == other.PreviousQuestsLinkedIDs;
	}

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		TSubclassOf<UQuestObject> QuestObjectClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		TArray<FName> PreviousQuestsLinkedIDs;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestStateChangedEvent, EQuestState, newQuestState);

/**
 * 
 */
UCLASS(Blueprintable)
class CESHI_API UQuestObject : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
		EQuestState GetCurrentQuestState() const {return CurrentQuestState;}

	UFUNCTION()
		void SetCurrentQuestState(EQuestState newState);

	UFUNCTION(BlueprintNativeEvent)
		bool GetQuestUnlockPrecondition();

	UFUNCTION(BlueprintImplementableEvent)
	void OnQuestBegin();

	UFUNCTION(BlueprintCallable)
	void CompleteQuest(bool Succeeded = true);

	class UWorld* GetWorld() const override;

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		bool GetTest(const UObject* WorldContextObject) {return true;};

	UFUNCTION(BlueprintCallable, Category = "Quest|Utilities", meta = (Latent, LatentInfo = "LatentInfo", Duration = "0.2", Keywords = "sleep"))
	void QuestDelay(float Duration, struct FLatentActionInfo LatentInfo);


public:
	UPROPERTY(BlueprintAssignable)
	FOnQuestStateChangedEvent OnQuestStateChanged;

private:
	UPROPERTY()
	EQuestState CurrentQuestState;
};
