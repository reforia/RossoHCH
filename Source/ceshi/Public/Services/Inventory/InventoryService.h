// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Services/ServiceBase.h"
#include "Engine/DataTable.h"
#include "InventoryService.generated.h"


class UCAC_InventoryComponent;
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
		: ID(""),
		Name(FText::FromString(TEXT(""))),
		Description(FText::FromString(TEXT(""))),
		Stackable(true),
		UIIcon(nullptr),
		Sprite(nullptr)
	{ }

	inline FStruct_Item& operator=(const FStruct_Item& other)
	{
		if (*this != other)
		{
			ID = other.ID;
			Name = other.Name;
			Description = other.Description;
			Stackable = other.Stackable;
			UIIcon = other.UIIcon;
			Sprite = other.Sprite;
		}
		return *this;
	}

	inline FStruct_Item& operator=(const FStruct_Item&& other)
	{
		if (*this != other)
		{
			delete UIIcon;
			//delete Sprite;

			ID = other.ID;
			Name = other.Name;
			Description = other.Description;
			Stackable = other.Stackable;
			UIIcon = other.UIIcon;
			Sprite = other.Sprite;
		}
		return *this;
	}
	inline bool operator==(const FStruct_Item & other)
	{
		return ID == other.ID;
	}
	inline bool operator!=(const FStruct_Item& other)
	{
		return ID != other.ID;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ID = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Name = FText::FromString(TEXT(""));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description = FText::FromString(TEXT(""));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Stackable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* UIIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPaperSprite* Sprite;
};

USTRUCT(BlueprintType)
struct FStruct_ItemWithCount
{
	GENERATED_USTRUCT_BODY()

public:
	FStruct_ItemWithCount()
		: ItemRef(),Count(1)
	{}
	FStruct_ItemWithCount(const FStruct_ItemWithCount& other) 
	{
		*this = other;
	}
	FStruct_ItemWithCount(FStruct_Item* otherItem) 
		: ItemRef(*otherItem),Count(1)
	{}
	FStruct_ItemWithCount(FStruct_Item* otherItem, int32 otherCount)
		: ItemRef(*otherItem), Count(otherCount)
	{}
	inline FStruct_ItemWithCount& operator=(const FStruct_ItemWithCount& other)
	{
		if (this != &other)
		{
			ItemRef = other.ItemRef;
			Count = other.Count;
		}
		return *this;
	}
	inline FStruct_ItemWithCount& operator=(FStruct_ItemWithCount&& other)
	{
		if (this != &other)
		{
			ItemRef = other.ItemRef;
			Count = other.Count;
		}
		return *this;
	}
	inline bool operator==(const FStruct_ItemWithCount& other)
	{
		return ItemRef == other.ItemRef && Count == other.Count;
	}

	UPROPERTY()
	FStruct_Item ItemRef;
	
	UPROPERTY()
	int32 Count;
};


USTRUCT()
struct Ftest32
{
	GENERATED_USTRUCT_BODY()

public:
	Ftest32() :a(0) {}

	UPROPERTY()
	int32 a = 0;
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
	bool AddObjectIntoInventory(const UCAC_InventoryComponent* inventoryCompRef, const FName itemID, const int32 count);

	UFUNCTION(BlueprintCallable, Category = "Construction")
	void RegisterInventoryComponent(UCAC_InventoryComponent* inventoryCompRef);

	FString GetDebugLogInfo() override;

	void ServiceConstruction(UServiceManager* owner) override;

	void ServiceShutdown() override;

private:
	TArray<UCAC_InventoryComponent*> GetListOfAllInventoryComps();

	bool DoesServiceContainComponent(const UCAC_InventoryComponent* inventoryCompRef);

	TArray<FStruct_ItemWithCount>* GetInventoryItemListByComponent(const UCAC_InventoryComponent* inventoryCompRef);

	FStruct_ItemWithCount* GetInventoryItemWithCountByComponent(const UCAC_InventoryComponent* inventoryCompRef, FName ItemID);

	FStruct_Item* GetInventoryItemByComponent(const UCAC_InventoryComponent* inventoryCompRef, FName ItemID);

private:
	TMap<UCAC_InventoryComponent*, TArray<FStruct_ItemWithCount>*> InventoriesList;

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UDataTable* ItemDatabase;


};
