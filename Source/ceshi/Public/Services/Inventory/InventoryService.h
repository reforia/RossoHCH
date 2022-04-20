// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Services/ServiceBase.h"
#include "Engine/DataTable.h"
#include "InventoryService.generated.h"

class UTexture2D;
class UDataTable;
class UPaperSprite;

USTRUCT(BlueprintType)
struct FStruct_Item : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FStruct_Item(const FStruct_Item& other)
	{
		*this = other;
	}
	
	FStruct_Item()
		: myID(""),
		myName(FText::FromString(TEXT(""))),
		myDescription(FText::FromString(TEXT(""))),
		myStackable(true),
		myUIIcon(nullptr),
		mySprite(nullptr)
	{ }

	inline FStruct_Item& operator=(const FStruct_Item& other)
	{
		if (*this != other)
		{
			myID = other.myID;
			myName = other.myName;
			myDescription = other.myDescription;
			myStackable = other.myStackable;
			myUIIcon = other.myUIIcon;
			mySprite = other.mySprite;
		}
		return *this;
	}

	inline FStruct_Item& operator=(const FStruct_Item&& other)
	{
		if (*this != other)
		{
			delete myUIIcon;
			//delete Sprite;

			myID = other.myID;
			myName = other.myName;
			myDescription = other.myDescription;
			myStackable = other.myStackable;
			myUIIcon = other.myUIIcon;
			mySprite = other.mySprite;
		}
		return *this;
	}
	inline bool operator==(const FStruct_Item & other)
	{
		return myID == other.myID;
	}
	inline bool operator!=(const FStruct_Item& other)
	{
		return myID != other.myID;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "ID"))
	FString myID = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Name"))
	FText myName = FText::FromString(TEXT(""));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Description"))
	FText myDescription = FText::FromString(TEXT(""));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Stackable"))
	bool myStackable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "UIIcon"))
	UTexture2D* myUIIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Sprite"))
	UPaperSprite* mySprite;
};

USTRUCT(BlueprintType)
struct FStruct_ItemWithCount
{
	GENERATED_USTRUCT_BODY()

public:
	FStruct_ItemWithCount()
		: myItemRef(),myCount(1)
	{}
	FStruct_ItemWithCount(const FStruct_ItemWithCount& other) 
	{
		*this = other;
	}
	FStruct_ItemWithCount(FStruct_Item* otherItem) 
		: myItemRef(*otherItem),myCount(1)
	{}
	FStruct_ItemWithCount(FStruct_Item* otherItem, int32 otherCount)
		: myItemRef(*otherItem), myCount(otherCount)
	{}
	inline FStruct_ItemWithCount& operator=(const FStruct_ItemWithCount& other)
	{
		if (this != &other)
		{
			myItemRef = other.myItemRef;
			myCount = other.myCount;
		}
		return *this;
	}
	inline FStruct_ItemWithCount& operator=(FStruct_ItemWithCount&& other)
	{
		if (this != &other)
		{
			myItemRef = other.myItemRef;
			myCount = other.myCount;
		}
		return *this;
	}
	inline bool operator==(const FStruct_ItemWithCount& other)
	{
		return myItemRef == other.myItemRef && myCount == other.myCount;
	}

	UPROPERTY()
	FStruct_Item myItemRef;
	
	UPROPERTY()
	int32 myCount;
};

/**
 * 
 */
UCLASS(Blueprintable)
class CESHI_API UInventoryService : public UServiceBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ItemOperation")
	bool AddObjectIntoInventory(const FName inventoryID, const FName itemID, const int32 count);

	UFUNCTION(BlueprintCallable, Category = "Construction")
	void RegisterInventoryID(FName inventoryID);

	FString GetDebugLogInfo() override;

	void ServiceConstruction(UServiceManager* owner) override;

	void ServiceShutdown() override;

private:
	UFUNCTION()
	TArray<FName> GetListOfAllInventoryIDs();

	UFUNCTION()
	bool DoesServiceContainInventoryID(const FName inventoryID);

	UFUNCTION()
	void ResetIntentoryEntry(FName inventoryID);

	TArray<FStruct_ItemWithCount>* GetInventoryItemListByInventoryID(const FName inventoryID);

	FStruct_ItemWithCount* GetInventoryItemWithCountByInventoryID(const FName inventoryID, FName itemID);

	FStruct_Item* GetInventoryItemByInventoryID(const FName inventoryID, FName itemID);

private:
	TMap<FName, TArray<FStruct_ItemWithCount>*> myInventoriesList;

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (DisplayName = "ItemDatabase"))
	class UDataTable* myItemDatabase;


};
