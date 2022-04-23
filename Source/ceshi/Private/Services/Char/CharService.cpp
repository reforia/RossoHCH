// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Char/CharService.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Components/CAC_CharComponent.h"

void UCharService::RegisterCharData(FName newID)
{
	if (DoesCharsContainData(newID))
		return;

	FStruct_CharData* charNewData = myCharDatabase->FindRow<FStruct_CharData>(newID, "");
	if (!charNewData)
		return;

	myChars.Add(charNewData);
}

bool UCharService::DoesCharsContainData(FName charID)
{
	for (FStruct_CharData* perCharData : myChars)
	{
		if (perCharData->myCharID == charID)
			return true;
	}
	return false;
}

FStruct_CharData* UCharService::GetCharDataByID(const FName charID)
{
	for (FStruct_CharData* charData : myChars)
	{
		if (charData->myCharID == charID)
			return charData;
	}

	return nullptr;
}

FString UCharService::GetDebugLogInfo()
{
	FString result;
	result = "----Char Service----\n";
	result = result + "Current available Chars: ";
	result.AppendInt(myChars.Num());
	result += "\n";
	for (FStruct_CharData* charData : myChars)
	{
		result = result + charData->myCharID.ToString() + "\n";
	}
	return result;
}

void UCharService::ServiceConstruction(UServiceManager* owner)
{
	myChars = TArray<FStruct_CharData*>();

	Super::ServiceConstruction(owner);
}

AActor* UCharService::GetCharActorInWorldByID(FName charID, const UObject* WorldContextObject)
{
	TArray<AActor*> pawns;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, APawn::StaticClass(), pawns);
	for (AActor* pawn : pawns)
	{
		UCAC_CharComponent* charCompRef = pawn->FindComponentByClass<UCAC_CharComponent>();
		if (!charCompRef)
			continue;;

		if (charCompRef->GetCharID() == charID)
			return pawn;
	}
	return nullptr;
}
