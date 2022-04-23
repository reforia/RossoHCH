// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Services/ServiceBase.h"
#include "Engine/DataTable.h"
#include "CharService.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FStruct_CharData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Char", meta = (DisplayName = "CharID"))
	FName myCharID;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Char", meta = (DisplayName = "CharName"))
	FName myCharName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Char", meta = (DisplayName = "CharTex"))
	UTexture2D* myCharTex;
};

class AActor;
/**
 * 
 */
UCLASS(Blueprintable)
class CESHI_API UCharService : public UServiceBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void RegisterCharData(FName newID);

	UFUNCTION()
	bool DoesCharsContainData(FName charID);

	TArray<FStruct_CharData*> GetAllChars() {return myChars;}

	FStruct_CharData* GetCharDataByID(const FName charID);

	FString GetDebugLogInfo() override;

	void ServiceConstruction(UServiceManager* owner) override;

	UFUNCTION()
	AActor* GetCharActorInWorldByID(FName charID, const UObject* WorldContextObject);

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "NPC", meta = (DisplayName = "CharDatabase"))
	class UDataTable* myCharDatabase;

private:
	TArray<FStruct_CharData*> myChars;
};
