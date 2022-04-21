// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Services/Quest/QuestType.h"
#include "Tickable.h"
#include "QuestObject.generated.h"

USTRUCT(BlueprintType)
struct FStruct_QuestData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FStruct_QuestData()
		: myQuestObjectClass(TSubclassOf<UQuestObject>()), myPreviousQuestsLinkedIDs(TArray<FName>())
	{}

	bool operator==(const FStruct_QuestData& other) const
	{
		return myQuestObjectClass == other.myQuestObjectClass
			&& myPreviousQuestsLinkedIDs == other.myPreviousQuestsLinkedIDs;
	}

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "QuestObjectClass"))
	TSubclassOf<UQuestObject> myQuestObjectClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "PreviousQuestsLinkedIDs"))
	TArray<FName> myPreviousQuestsLinkedIDs;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestStateChangedEvent, EQuestState, newQuestState);

class AActor;
/**
 * 
 */
UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class CESHI_API UQuestObject : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
		EQuestState GetCurrentQuestState() const {return myCurrentQuestState;}

	UFUNCTION()
		void SetCurrentQuestState(EQuestState newState);

	UFUNCTION(BlueprintNativeEvent)
		bool GetQuestUnlockPrecondition();

	UFUNCTION(BlueprintImplementableEvent)
	void OnQuestBegin();

	UFUNCTION(BlueprintCallable)
	void CompleteQuest(bool Succeeded = true);

	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable, Category = "Quest|Utilities", meta = (Latent, LatentInfo = "LatentInfo", Duration = "0.2", Keywords = "sleep"))
	void QuestDelay(float Duration, struct FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintPure, Category = "Quest|Utilities")
	UObject* QuestGetWorldContext() { return this; }

	UFUNCTION(BlueprintPure, Category = "Quest|Utilities")
	AActor* QuestGetCharActorByID(FName charID);

public:
	UPROPERTY(BlueprintAssignable)
	FOnQuestStateChangedEvent OnQuestStateChanged;

private:
	UPROPERTY()
	EQuestState myCurrentQuestState;
};
