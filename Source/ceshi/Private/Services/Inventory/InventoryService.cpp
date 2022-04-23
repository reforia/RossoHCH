// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Inventory/InventoryService.h"
#include "Engine/Texture2D.h"
#include "Services/ServiceManager.h"

void UInventoryService::ServiceConstruction(UServiceManager* owner)
{	
	myInventoriesList = TMap<FName, TArray<FStruct_ItemWithCount>*>();
	
	UServiceBase::ServiceConstruction(owner);
}

void UInventoryService::ServiceShutdown()
{
	for (auto inventoryID : GetListOfAllInventoryIDs())
	{
		ResetIntentoryEntry(inventoryID);
	}
	myInventoriesList.Reset();
}

bool UInventoryService::AddObjectIntoInventory(const FName inventoryID, const FName itemID, const int32 count)
{
	if(!DoesServiceContainInventoryID(inventoryID))
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, "[CRITICAL ERROR] TRY ADD OBJECT TO INVENTORY BUT INVENTORY COMP NOT VALID (nullptr or Not Initialized)");
		return false;
	}

	auto item = GetInventoryItemWithCountByInventoryID(inventoryID, itemID);
	if (!item)
	{
		// We need to add it into the array list
		if (count <= 0)
			return true;

		auto itemsList = GetInventoryItemListByInventoryID(inventoryID);
		if (!itemsList)
			return false;
		
		FStruct_Item* itemQueryData = myItemDatabase->FindRow<FStruct_Item>(itemID, "");
		if (!itemQueryData)
			return false;

		const int unstackableCount = FMath::Clamp(count, 0, 1);
		const int stackableCount = FMath::Max(count, 0);
		const int finalCount = itemQueryData->myStackable ? stackableCount : unstackableCount;
		FStruct_ItemWithCount tmpItemWithCount(itemQueryData, finalCount);

		itemsList->Add(tmpItemWithCount);
		return true;
	}
	else
	{
		// We need to add the count up
		int targetCount = item->myCount + count;
		int unstackableCount = FMath::Clamp(targetCount, 0, 1);
		int stackableCount = FMath::Max(targetCount, 0);
		int finalCount = item->myItemRef.myStackable ? stackableCount : unstackableCount;
		if (finalCount > 0)
		{
			// We are adding stuff to existing item
			item->myCount = finalCount;
			return true;
		}
		else 
		{
			// We are clearing the array
			auto currentItemsList = GetInventoryItemListByInventoryID(inventoryID);
			int32 index = 0;
			for (auto &items : *currentItemsList)
			{
				if (items.myItemRef.myID == item->myItemRef.myID)
					break;
				
				index++;
			}
			
			if (!currentItemsList->IsValidIndex(index))
				return false;

			currentItemsList->RemoveAt(index);
			return true;
		}
	}
	return false;
}

void UInventoryService::RegisterInventoryID(FName inventoryID)
{
	if (DoesServiceContainInventoryID(inventoryID))
		return; // Already Registered before

	myInventoriesList.Add(inventoryID, new TArray<FStruct_ItemWithCount>());
}

int32 UInventoryService::GetItemCountByID(FName inventoryID, FName itemID)
{
	FStruct_ItemWithCount* itemWithCount = GetInventoryItemWithCountByInventoryID(inventoryID, itemID);
	if (itemWithCount)
		return itemWithCount->myCount;

	return 0;
}

FString UInventoryService::GetDebugLogInfo()
{
	FString result;
	result = "-----INVENTORY Debug Log-----\n";
	for (FName inventoryID : GetListOfAllInventoryIDs())
	{
		result = result + "Inventory ID: " + inventoryID.ToString() + "\n";
		for (FStruct_ItemWithCount& itemsList : *GetInventoryItemListByInventoryID(inventoryID))
		{
			result += "-----------------------\n";
			result = result + "Name: " + itemsList.myItemRef.myName.ToString();
			result = result + "Count: ";
			result.AppendInt(itemsList.myCount);
			result += "\n";
		}
	}

	return result;
}

bool UInventoryService::DoesServiceContainInventoryID(const FName inventoryID)
{
	return GetListOfAllInventoryIDs().Contains(inventoryID);
}

TArray<FName> UInventoryService::GetListOfAllInventoryIDs()
{
	TArray<FName> result;

	int32 a = myInventoriesList.Num();
	if (a == 0)
		return result;

	myInventoriesList.GetKeys(result);
	return result;
}

void UInventoryService::ResetIntentoryEntry(FName inventoryID)
{
	if (!DoesServiceContainInventoryID(inventoryID))
		return;
	
	delete myInventoriesList[inventoryID];
	myInventoriesList[inventoryID] = nullptr;
	myInventoriesList.Remove(inventoryID);
}

TArray<FStruct_ItemWithCount>* UInventoryService::GetInventoryItemListByInventoryID(const FName inventoryID)
{
	if (!DoesServiceContainInventoryID(inventoryID))
		return nullptr;

	return myInventoriesList[inventoryID];
}

FStruct_ItemWithCount* UInventoryService::GetInventoryItemWithCountByInventoryID(const FName inventoryID, FName ItemID)
{
	if (!myItemDatabase)
		return nullptr;

	FStruct_Item* queryItemResult = myItemDatabase->FindRow<FStruct_Item>(ItemID, "");

	if (!queryItemResult)
		return nullptr;

	auto inventoryItemsList = GetInventoryItemListByInventoryID(inventoryID);
	if (!inventoryItemsList)
		return nullptr;

	for (auto& items : *inventoryItemsList)
	{
		if (items.myItemRef.myID == queryItemResult->myID)
			return &items;
	}

	return nullptr;
}

FStruct_Item* UInventoryService::GetInventoryItemByInventoryID(const FName inventoryID, FName itemID)
{
	auto items = GetInventoryItemWithCountByInventoryID(inventoryID, itemID);

	if (!items)
		return nullptr;

	return &items->myItemRef;
}


