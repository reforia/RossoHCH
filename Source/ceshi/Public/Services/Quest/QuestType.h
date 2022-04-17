// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
//#include "Services/Quest/QuestObject.h"
#include "QuestType.generated.h"

UENUM(BlueprintType)
enum class EQuestLineState : uint8
{
	EV_Locked UMETA(DisplayName = "Locked"),
	EV_Unlocked UMETA(DisplayName = "Unlocked"),
	EV_Finished UMETA(DisplayName = "Finished"),
};

UENUM(BlueprintType)
enum class EQuestState : uint8
{
	EV_Locked UMETA(DisplayName = "Locked"),
	EV_Unlocked UMETA(DisplayName = "Unlocked"),
	EV_InProgress UMETA(DisplayName = "InProgress"),
	EV_Succeeded UMETA(DisplayName = "Succeeded"),
	EV_Failed UMETA(DisplayName = "Failed")
};



