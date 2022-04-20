// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Services/Quest/QuestType.h"
#include "Services/Quest/QuestObject.h"
#include "Engine/DataTable.h"
#include "Tickable.h"
#include "QuestContextObject.generated.h"

class UDataTable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestlineStateChangedEvent, EQuestLineState, newState);
/**
 * 
 */
UCLASS(Blueprintable)
class CESHI_API UQuestContextObject : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	UQuestContextObject();
	virtual ~UQuestContextObject();

	UFUNCTION(BlueprintPure)
		const EQuestLineState GetCurrentQuestLineState() { return myCurrentQuestLineState; }

	UFUNCTION()
		void UpdateCurrentQuestLineState();

	UFUNCTION()
		void InitializeCurrentQuestLine();

	UFUNCTION()
		UQuestObject* GetQuestObjectByID(FName ID);

	UFUNCTION()
		void GetAllQuestObjects(TArray<UQuestObject*>& outQuestList);

	// Tick-able Interface
	TStatId GetStatId() const override { return Super::GetStatID(); };

	void Tick(float DeltaTime) override;

	bool IsTickable() const override { return true; };

private:
	UFUNCTION()
		void SetCurrentQuestLineState(EQuestLineState newState);

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UDataTable* myQuestLineDatabase;

	UPROPERTY()
	bool myShouldTick = false;

private:
	UPROPERTY()
		EQuestLineState myCurrentQuestLineState = EQuestLineState::EV_Locked;

	UPROPERTY(BlueprintAssignable)
		FOnQuestlineStateChangedEvent OnQuestlineStateChanged;

	UPROPERTY()
	TMap<UQuestObject*, FStruct_QuestData> myQuestsInQuestLine = TMap<UQuestObject*, FStruct_QuestData>();

};
